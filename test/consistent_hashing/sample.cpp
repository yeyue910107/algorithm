#include <stdio.h>
#include <stdlib.h>

#include "conhash.h"

struct node_s nodes[64];

int main() {
	const struct node_s *node;
	char str[128];
	long hashes[512];
	const int num = 5;
	const int times = 20;

	struct conhash_s *conhash = conhash_init(NULL);
	if (conhash) {
		conhash_set_node(&nodes[0], "ac milan", 32);
		conhash_set_node(&nodes[1], "man city", 24);
		conhash_set_node(&nodes[2], "paris saint-german", 25);
		conhash_set_node(&nodes[3], "valencia", 10);
		conhash_set_node(&nodes[4], "munchen 1860", 48);

		for (int i = 0; i < num; i++)
			conhash_add_node(conhash, &nodes[i]);
		printf("virtual nodes number %d\n", conhash_get_vnodes_num(conhash));
		printf("the hashing results------------------------------\n");

		for (int i = 0; i < times; i++) {
			sprintf(str, "yeyue%03d", i);
			node = conhash_lookup(conhash, str);
			if (node)
				printf("[%16s] is in node: [%16s]\n", str, node->iden);
		}
		conhash_get_vnodes(conhash, hashes, sizeof(hashes)/sizeof(hashes[0]));
		conhash_del_node(conhash, &nodes[2]);
		printf("remove node[%s], virtual nodes number %d\n", 
			nodes[2].iden, conhash_get_vnodes_num(conhash));
		printf("the hashing results-------------------------------\n");
		for (int i = 0; i < times; i++) {
			sprintf(str, "yeyue%03d", i);
			node = conhash_lookup(conhash, str);
			if (node)
				printf("[%16s] is in node: [%16s]\n", str, node->iden);
		}
	}
	conhash_fin(conhash);
	return 0;
}