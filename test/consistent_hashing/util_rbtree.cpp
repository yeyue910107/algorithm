#include "util_rbtree.h"

/* null node */
#define _NULL(rbtree) (&((rbtree)->null))

struct rbtree_check_s {
	short rbh; /* rb height */
	short maxd; /* max depth */
	int fini; /* check failed */
	const util_rbtree_node_t *null; /* sentinel */
};

typedef struct rbtree_check_s rbtree_check_t;

static void rbtree_insert_fixup(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node);
static void rbtree_delete_fixup(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node);
static void rbtree_left_rotate(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node);
static void rbtree_right_rotate(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node);

void util_rbtree_init(util_rbtree_t *rbtree) {
	if (rbtree != NULL) {
		util_rbt_black(_NULL(rbtree));
		rbtree->root = _NULL(rbtree);
		rbtree->size = 0;
	}
}

util_rbtree_node_t* util_rbsubtree_min(util_rbtree_node_t *node, 
	util_rbtree_node_t *sentinel) {
	if (node == sentinel)
		return NULL;
	while (node->left != sentinel)
		node = node->left;
	return node;
}

util_rbtree_node_t* util_rbsubtree_max(util_rbtree_node_t *node, 
	util_rbtree_node_t *sentinel) {
	if (node == sentinel)
		return NULL;
	while (node->right != sentinel)
		node = node->right;
	return node;
}

void util_rbtree_insert(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node) {
	util_rbtree_node_t *x, *y;
	if ((rbtree == NULL) || (node == NULL) || (node == _NULL(rbtree)))
		return;
	/* the tree is empty */
	if (rbtree->root == _NULL(rbtree)) {
		rbtree->root = node;
		node->parent = _NULL(rbtree);
	}
	/* find the insert position */
	else {
		x = rbtree->root;
		while (x != _NULL(rbtree)) {
			y = x;
			if (node->key < x->key)
				x = x->left;
			else
				x = x->right;
		}
		/* y is node's parent */
		node->parent = y;
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}

	/* init node's link and color */
	node->left = _NULL(rbtree);
	node->right = _NULL(rbtree);
	util_rbt_red(node);
	/* fix up insert */
	rbtree_insert_fixup(rbtree, node);
	rbtree->size++;
}

/* insert may violate the rbtree properties, fix up the tree */
void rbtree_insert_fixup(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node) {
	util_rbtree_node_t *p, *u;

	while (util_rbt_isred(node->parent)) {
		p = node->parent;
		if (p == p->parent->left) {
			u = p->parent->right;
			if (util_rbt_isred(u)) { /* case 1: p & u are red */
				util_rbt_black(u);
				util_rbt_black(p);
				util_rbt_red(p->parent);
				node = p->parent;
			}
			else {
				if (node == p->right) { /* case 2: p is red, u is black, node is right child */
					node = p;
					rbtree_left_rotate(rbtree, node);
					p = node->parent;
				}
				/* case 3: p is red, u is black, node is left child */
				util_rbt_black(p);
				util_rbt_red(p->parent);
				rbtree_right_rotate(rbtree, p->parent);
			}
		}
		else {
			u = p->parent->left;
			if (util_rbt_isred(u)) { /* case 1: p & u are red */
				util_rbt_black(u);
				util_rbt_black(p);
				util_rbt_red(p->parent);
				node = p->parent;
			}
			else {
				if (node == p->left) { /* case 2: p is red, u is black, node is left child */
					node = p;
					rbtree_right_rotate(rbtree, node);
					p = node->parent;
				}
				/* case 3: p is red, u is black, node is right child */
				util_rbt_black(p);
				util_rbt_red(p->parent);
				rbtree_left_rotate(rbtree, p->parent);
			}
		}
	}
	util_rbt_black(rbtree->root);
}

void util_rbtree_delete(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node) {
	int isblack;
	util_rbtree_node_t *temp, *subst;
	if ((rbtree == NULL) || (node == NULL) || (node == _NULL(rbtree)))
		return;
	rbtree->size--;
	/* find deleted position, indicated by temp */
	if (node->left == _NULL(rbtree)) {
		temp = node;
		subst = node->right;
	}
	else if (node->right == _NULL(rbtree)) {
		temp = node;
		subst = node->left;
	}
	else { /* right and left are not null */
		temp = util_rbsubtree_min(node->right, _NULL(rbtree));
		if (temp->left != _NULL(rbtree))
			subst = temp->left;
		else
			subst = temp->right;
	}
	if (temp == rbtree->root) {
		rbtree->root = subst;
		util_rbt_black(subst);
		rbt_clear_node(temp);
		return;
	}
	isblack = util_rbt_isblack(temp);
	subst->parent = temp->parent;
	if (temp == temp->parent->left)
		temp->parent->left = subst;
	else
		temp->parent->right = subst;

	if (temp != node) {
		temp->parent = node->parent;
		if (node == rbtree->root)
			rbtree->root = temp;
		else {
			if (node->parent->left == node)
				node->parent->left = temp;
			else
				node->parent->right = temp;
		}
		temp->right = node->right;
		temp->left = node->left;
		if (temp->left != _NULL(rbtree))
			temp->left->parent = temp;
		if (temp->right != _NULL(rbtree))
			temp->right->parent = temp;
		temp->color = node->color;
		temp->key = node->key;
		temp->data = node->data;
	}
	rbt_clear_node(node);
	if (isblack)
		rbtree_delete_fixup(rbtree, subst);
}

void rbtree_delete_fixup(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node) {
	int h = 0;
	util_rbtree_node_t *w;
	while ((node != rbtree->root) && util_rbt_isblack(node)) {
		h++;
		if (node == node->parent->left) {
			w = node->parent->right;
			if (util_rbt_isred(w)) {
				util_rbt_black(w);
				util_rbt_red(node->parent);
				rbtree_left_rotate(rbtree, node->parent);
				w = node->parent->right;
			}
			if (util_rbt_isblack(w->left) && util_rbt_isblack(w->right)) {
				util_rbt_red(w);
				node = node->parent;
			}
			else {
				if (util_rbt_isblack(w->right)) {
					util_rbt_black(w->left);
					util_rbt_red(w);
					rbtree_right_rotate(rbtree, w);
					w = node->parent->right;
				}
				w->color = node->parent->color;
				util_rbt_black(node->parent);
				util_rbt_black(w->right);
				rbtree_left_rotate(rbtree, node->parent);
				node = rbtree->root;
			}
		}
		else {
			w = node->parent->left;
			if (util_rbt_isred(w)) {
				util_rbt_black(w);
				util_rbt_red(node->parent);
				rbtree_right_rotate(rbtree, node->parent);
				w = node->parent->left;
			}
			if (util_rbt_isblack(w->left) && util_rbt_isblack(w->right)) {
				util_rbt_red(w);
				node = node->parent;
			}
			else {
				if (util_rbt_isblack(w->left)) {
					util_rbt_black(w->right);
					util_rbt_red(w);
					rbtree_left_rotate(rbtree, w);
					w = node->parent->left;
				}
				w->color = node->parent->color;
				util_rbt_black(node->parent);
				util_rbt_black(w->left);
				rbtree_right_rotate(rbtree, node->parent);
				node = rbtree->root;
			}
		}
		util_rbt_black(node);
	}
}

void rbtree_left_rotate(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node) {
	util_rbtree_node_t *rc = node->right;
	util_rbtree_node_t *rclc = rc->left;
	/* make rc to replace node's position */
	rc->parent = node->parent;
	if (node == rbtree->root)
		rbtree->root = rc;
	else {
		if (node->parent->left == node)
			node->parent->left = rc;
		else
			node->parent->right = rc;
	}
	/* make node to be rc's left child */
	node->parent = rc;
	rc->left = node;
	node->right = rclc;
	if (rclc != _NULL(rbtree))
		rclc->parent = node;
}

void rbtree_right_rotate(util_rbtree_t *rbtree, 
	util_rbtree_node_t *node) {
	util_rbtree_node_t *lc = node->left;
	util_rbtree_node_t *lcrc = lc->right;

	lc->parent = node->parent;
	if (node == rbtree->root)
		rbtree->root = lc;
	else {
		if (lc->parent->left == node)
			lc->parent->left = lc;
		else
			lc->parent->right = lc;
	}
	node->parent = lc;
	lc->right = node;
	node->left = lcrc;
	if (lcrc != _NULL(rbtree))
		lcrc->parent = node;
}

util_rbtree_node_t* util_rbtree_search(util_rbtree_t *rbtree, long key) {
	if (rbtree != NULL) {
		util_rbtree_node_t *node = rbtree->root;
		util_rbtree_node_t *null = _NULL(rbtree);
		while (node != null) {
			if (key == node->key)
				return node;
			else if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}
	}
	return NULL;
}

util_rbtree_node_t *util_rbtree_lookup(util_rbtree_t *rbtree, long key) {
	if ((rbtree != NULL) && !util_rbtree_isempty(rbtree)) {
		util_rbtree_node_t *node = NULL;
		util_rbtree_node_t *temp = rbtree->root;
		util_rbtree_node_t *null = _NULL(rbtree);
		while (temp != null) {
			if (key <= temp->key) {
				node = temp;
				temp = temp->left;
			}
			else
				temp = temp->right;
		}
		return (node != NULL) ? node : util_rbtree_min(rbtree);
	}
	return NULL;
}

/* check a tree is a rbtree or not 
 * return 0: yes
 * return 1: root is not black
 * return 2: node is in other color than black and red
 * return 3: tree's black height is not unique
 * return 4: a red node with parent in red exists
 * return 5: volatile binary search properties
 */
static void rbtree_check_subtree(const util_rbtree_node_t *node, 
	rbtree_check_t *check, int level, int curheight) {
	if (check->fini)
		return;
	if (util_rbt_isblack(node))
		curheight++;
	else if (!util_rbt_isred(node)) {
		check->fini = OTHER_COLOR;
		return;
	}
	/* check left */
	if (node->left != check->null) {
		if (util_rbt_isred(node) && util_rbt_isred(node->left)) {
			check->fini = REDNODE_PARENT_ISRED;
			return;
		}
		if (node->key < node->left->key) {
			check->fini = NOT_BINSEARCH;
			return;
		}
		rbtree_check_subtree(node->left, check, level + 1, curheight);
	}
	else
		goto __check_rb_height;
	if (node->right != check->null) {
		if (util_rbt_isred(node) && util_rbt_isred(node->right)) {
			check->fini = REDNODE_PARENT_ISRED;
			return;
		}
		if (node->key > node->right->key) {
			check->fini = NOT_BINSEARCH;
			return;
		}
		rbtree_check_subtree(node->right, check, level + 1, curheight);
	}
	else
		goto __check_rb_height;
	return;
__check_rb_height:
	if (check->rbh == 0)
		check->rbh = curheight;
	if (check->maxd < level)
		check->maxd = level;
	if (check->rbh != curheight)
		check->fini = RBH_NOT_UNIQUE;
}

int util_rbtree_check(const util_rbtree_t *rbtree, 
	int *blackheight, int *maxdepth) {
	rbtree_check_t check;
	if (rbtree->root == _NULL(rbtree))
		return IS_RBTREE;
	if (!util_rbt_isblack(rbtree->root))
		return ROOT_NOT_BLACK;
	check.fini = check.maxd = check.rbh = 0;
	check.null = _NULL(rbtree);
	rbtree_check_subtree(rbtree->root, &check, 1, 0);
	if (blackheight)
		*blackheight = check.rbh;
	if (maxdepth)
		*maxdepth = check.maxd;
	return check.fini;
}

static void rbtree_mid_travel(util_rbtree_node_t *node, util_rbtree_node_t *sentinel, 
	void(*opera)(util_rbtree_node_t *, void *), void *data) {
	if (node->left != sentinel)
		rbtree_mid_travel(node->left, sentinel, opera, data);
	opera(node, data);
	if (node->right != sentinel)
		rbtree_mid_travel(node->right, sentinel, opera, data);
}

void util_rbtree_mid_travel(util_rbtree_t *rbtree, 
	void(*opera)(util_rbtree_node_t *, void *), void *data) {
	if (rbtree != NULL && !util_rbtree_isempty(rbtree))
		rbtree_mid_travel(rbtree->root, _NULL(rbtree), opera, data);
}