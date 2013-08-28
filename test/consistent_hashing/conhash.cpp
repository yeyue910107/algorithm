#include "conhash.h"
#include "conhash_inter.h"

struct conhash_s* conhash_init(conhash_cb_hashfunc pfhash) {
	struct conhash_s *conhash = (struct conhash_s *)calloc(1, 
		sizeof(struct conhash_s));
	if (conhash == NULL)
		return NULL;
	do {
		if (pfhash != NULL)
			conhash->cb_hashfunc = pfhash;
		else
			conhash->cb_hashfunc = __conhash_hash_def;
		util_rbtree_init(&conhash->vnode_tree);
		return conhash;
	}
	while (0);
	free(conhash);
	return NULL;
}

void conhash_fin(struct conhash_s *conhash) {
	if (conhash != NULL) {
		while (!util_rbtree_isempty(&conhash->vnode_tree)) {
			util_rbtree_node_t *rbnode = conhash->vnode_tree.root;
			util_rbtree_delete(&conhash->vnode_tree, rbnode);
			__conhash_del_rbnode(rbnode);
		}
		free(conhash);
	}
}

void conhash_set_node(struct node_s *node, const char *iden, u_int replica) {
	strncpy(node->iden, iden, sizeof(node->iden) - 1);
	node->replicas = replica;
	node->flag = NODE_FLAG_INIT;
}

int conhash_add_node(struct conhash_s *conhash, struct node_s *node) {
	if (conhash == NULL || node == NULL)
		return -1;
	if (!(node->flag&NODE_FLAG_INIT) || (node->flag&NODE_FLAG_IN))
		return -1;
	node->flag |= NODE_FLAG_IN;
	__conhash_add_replicas(conhash, node);
	return 0;
}

int conhash_del_node(struct conhash_s *conhash, struct node_s *node) {
	if (conhash == NULL || node == NULL)
		return -1;
	if (!(node->flag&NODE_FLAG_INIT) || !(node->flag&NODE_FLAG_IN))
		return -1;
	node->flag &= (~NODE_FLAG_IN);
	__conhash_del_replicas(conhash, node);
	return 0;
}

const struct node_s* conhash_lookup(const struct conhash_s *conhash, 
	const char *object) {
	long hash;
	const util_rbtree_node_t *rbnode;
	if (conhash == NULL || conhash->ivnodes == 0 || object == NULL)
		return NULL;
	hash = conhash->cb_hashfunc(object);
	rbnode = util_rbtree_lookup(const_cast<util_rbtree_t*>(&(conhash->vnode_tree)), hash);
	if (rbnode != NULL)
		return ((struct virtual_node_s*)(rbnode->data))->node;
	return NULL;
}