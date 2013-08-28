#include <stdio.h>
#include <stdlib.h>

#include "util_rbtree.h"

#define NODES_NUM 64

void create_test_data(util_rbtree_node_t *nodes[], const int num) {
	for (int i = 0; i < num; i++) {
		nodes[i] = (util_rbtree_node_t *)malloc(sizeof(util_rbtree_node_t));
		nodes[i]->key = i;
		nodes[i]->color = 0xff;
		nodes[i]->left = nodes[i]->right = nodes[i]->parent = NULL;
		nodes[i]->data = NULL;
	}
}

void delete_test_data(util_rbtree_node_t *nodes[], const int num) {
	for (int i = 0; i < num; i++) {
		free(nodes[i]);
	}
}

void opera(util_rbtree_node_t *node, void *data) {
	printf("visit node %d\n", node->key);
}

int main() {
	const int num = 15;
	util_rbtree_node_t *nodes[NODES_NUM];
	util_rbtree_t *rbtree = (util_rbtree_t *)malloc(sizeof(util_rbtree_t));
	util_rbtree_init(rbtree);
	create_test_data(nodes, num);
	for (int i = 0; i < num; i++)
		util_rbtree_insert(rbtree, nodes[i]);
	util_rbtree_mid_travel(rbtree, opera, NULL);
	for (int i = num - 1; i >= 0; i--) {
		util_rbtree_delete(rbtree, nodes[i]);
	}
	delete_test_data(nodes, num);
	free(rbtree);
	return 0;
}