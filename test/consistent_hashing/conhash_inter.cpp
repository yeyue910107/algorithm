#include "conhash_inter.h"
#include "conhash.h"

/* default hash function, using md5 */
long __conhash_hash_def(const char *instr) {
	int i;
	long hash = 0;
	unsigned char digest[16];
	conhash_md5_digest((const u_char *)instr, digest);

	for (i = 0; i < 4; i++) {
		hash += ((long)(digest[i*4 + 3]&0xff) << 24)
			| ((long)(digest[i*4 + 2]&0xff) << 16)
			| ((long)(digest[i*4 + 1]&0xff) << 8)
			| ((long)(digest[i*4 + 0]&0xff));
	}
	return hash;
}

void __conhash_node2string(const struct node_s *node, u_int replica_idx, 
	char buf[128], u_int *len) {
#if (defined (WIN32) || defined (__WIN32))
	_snprintf_s(buf, 127, _TRUNCATE, "%s-%03d", node->iden, replica_idx);
#else
	snprintf(buf, 127, "%s-%03d", node->iden, replica_idx);
#endif
}

void __conhash_add_replicas(struct conhash_s *conhash, struct node_s *node) {
	u_int i, len;
	long hash;
	char buf[128];
	util_rbtree_node_t *rbnode;
	for (i = 0; i < node->replicas; i++) {
		/* calc hash value of all virtual nodes */
		__conhash_node2string(node, i, buf, &len);
		hash = conhash->cb_hashfunc(buf);
		/* add virtual node, check replication */
		if (util_rbtree_search(&conhash->vnode_tree, hash) == NULL) {
			rbnode = __conhash_get_rbnode(node, hash);
			if (rbnode != NULL) {
				util_rbtree_insert(&conhash->vnode_tree, rbnode);
				conhash->ivnodes++;
			}
		}
	}
}

void __conhash_del_replicas(struct conhash_s *conhash, struct node_s *node) {
	u_int i, len;
	long hash;
	char buf[128];
	struct virtual_node_s *vnode;
	util_rbtree_node_t *rbnode;

	for (i = 0; i < node->replicas; i++) {
		/* calc hash value of all virtual nodes */
		__conhash_node2string(node, i, buf, &len);
		hash = conhash->cb_hashfunc(buf);
		rbnode = util_rbtree_search(&conhash->vnode_tree, hash);
		if (rbnode != NULL) {
			vnode = (struct virtual_node_s*)rbnode->data;
			if (vnode->hash == hash && vnode->node == node) {
				conhash->ivnodes--;
				util_rbtree_delete(&conhash->vnode_tree, rbnode);
				__conhash_del_rbnode(rbnode);
			}
		}
	}
}

util_rbtree_node_t *__conhash_get_rbnode(struct node_s *node, long hash) {
	util_rbtree_node_t *rbnode;
	rbnode = (util_rbtree_node_t *)malloc(sizeof(util_rbtree_node_t));
	if (rbnode != NULL) {
		rbnode->key = hash;
		rbnode->data = malloc(sizeof(struct virtual_node_s));
		if (rbnode->data != NULL) {
			struct virtual_node_s *vnode = (struct virtual_node_s *)rbnode->data;
			vnode->hash = hash;
			vnode->node = node;
		}
		else {
			free(rbnode);
			rbnode = NULL;
		}
	}
	return rbnode;
}

void __conhash_del_rbnode(util_rbtree_node_t *rbnode) {
	struct virtual_node_s *node = (struct virtual_node_s *)rbnode->data;
	free(node);
	free(rbnode);
}