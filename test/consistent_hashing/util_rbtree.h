#ifndef __UTIL_RBTREE_H_
#define __UTIL_RBTREE_H_

#include "global.h"
#include <stdlib.h>

typedef struct util_rbtree_s util_rbtree_t;
typedef struct util_rbtree_node_s util_rbtree_node_t;

struct util_rbtree_node_s {
	long key;
	util_rbtree_node_t *parent;
	util_rbtree_node_t *right;
	util_rbtree_node_t *left;
	int color;
	void *data;
};

struct util_rbtree_s {
	util_rbtree_node_t *root;
	util_rbtree_node_t null;
	u_int size;
};

#define util_rbt_black(rbnode) ((rbnode)->color = 1)
#define util_rbt_red(rbnode) ((rbnode)->color = 0)
#define util_rbt_isblack(rbnode) ((rbnode)->color == 1)
#define util_rbt_isred(rbnode) ((rbnode)->color == 0)

/* clear a node */
#define rbt_clear_node(node) do { \
	node->left = NULL; \
	node->right = NULL; \
	node->parent = NULL; \
	}while(0)

/* is the tree empty */
#define util_rbtree_isempty(rbtree) ((rbtree)->root == &(rbtree)->null)

/* find the min node */
#define util_rbtree_min(rbtree) util_rbsubtree_min((rbtree)->root, &(rbtree)->null)

/* find the max node */
#define util_rbtree_max(rbtree) util_rbsubtree_max((rbtree)->root, &(rbtree)->null)

void util_rbtree_init(util_rbtree_t *rbtree);

void util_rbtree_insert(util_rbtree_t *rbtree, util_rbtree_node_t *node);

void util_rbtree_delete(util_rbtree_t *rbtree, util_rbtree_node_t *node);

/* search node with key = @key in the tree */
util_rbtree_node_t* util_rbtree_search(util_rbtree_t *rbtree, long key);

/* look up the node int the tree
 * return the first node with key >= @key */
util_rbtree_node_t* util_rbtree_lookup(util_rbtree_t *rbtree, long key);

/* find the min node of subtree */
util_rbtree_node_t* util_rbsubtree_min(util_rbtree_node_t *node, 
	util_rbtree_node_t *sentinel);

/* find the max node of subtree */
util_rbtree_node_t* util_rbsubtree_max(util_rbtree_node_t *node, 
	util_rbtree_node_t *sentinel);

#define IS_RBTREE 0
#define ROOT_NOT_BLACK 1
#define OTHER_COLOR 2
#define RBH_NOT_UNIQUE 3
#define REDNODE_PARENT_ISRED 4
#define NOT_BINSEARCH 5
/* check a tree is a rbtree or not 
 * return 0: yes
 * return 1: root is not black
 * return 2: node is in other color than black and red
 * return 3: tree's black height is not unique
 * return 4: a red node with parent in red exists
 * return 5: volatile binary search properties
 */
int util_rbtree_check(const util_rbtree_t *rbtree, 
	int *blackheight, int *maxdepth);

/* traverse through a rbtree in order */
void util_rbtree_mid_travel(util_rbtree_t *rbtree, 
	void(*opera)(util_rbtree_node_t *, void *), void *data);


#endif