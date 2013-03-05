#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <list>

template <class T>
struct BTNode{
	T data;
	BTNode *left, *right, *parent;
	BTNode() : left(NULL), right(NULL), parent(NULL){ }
	BTNode(T data) : data(data), left(NULL), right(NULL), parent(NULL) { }
	BTNode(T data, BTNode *parent) : data(data), parent(parent), left(NULL), right(NULL) { }
};

template <class T>
class BSTree {
public:
	BSTree() : root(NULL){ }
	~BSTree() { delete root; }
	bool is_empty() { return (root != NULL ? true : false); }
	void print() { layer_order(); };
	BTNode<T>* insert(const T &);
	BTNode<T>* search(const T &);
	void remove(const T &);
	static BTNode<T>* get_max(BTNode<T>*);
	static BTNode<T>* get_min(BTNode<T>*);
	BTNode<T>* successor(BTNode<T> *);
	BTNode<T>* predecessor(BTNode<T> *);
	void pre_order();
	void in_order();
	void post_order();
	void layer_order();
	int depth();
private:
	BTNode<T> *root;
	BTNode<T>* search(const T &, BTNode<T> *);
	BTNode<T>* insert(const T &, BTNode<T> *&);
	static int depth(BTNode<T> *);
};

template <class T>
BTNode<T>* BSTree<T>::search(const T &data) {
	return search(data, root);
}

template <class T>
BTNode<T>* BSTree<T>::search(const T &data, BTNode<T> *node) {
	if (node != NULL) {
		if (data == node->data)
			return node;
		else if (data > node->data)
			search(data, node->right);
		else
			search(data, node->left);
	}
	return NULL;
}

template <class T>
BTNode<T>* BSTree<T>::insert(const T &data) {
	return insert(data, root);
}

template <class T>
BTNode<T>* BSTree<T>::insert(const T &data, BTNode<T> *&node) {
	/*if (node == NULL) {
		node = new BTNode<T>(data);
		if (root == NULL)
			root = node;
		return node;
	}
	if (data == node->data)
		return NULL;
	if (data < node->data){
		if (node->left == NULL) {
			node->left = new BTNode<T>(data);
			node->left->parent = node;
			return node->left;
		}
		return insert(data, node->left);
	}
	if (data > node->data) {
		if (node->right == NULL) {
			node->right = new BTNode<T>(data);
			node->right->parent = node;
			return node->right;
		}
		return insert(data, node->right);
	}
	return NULL;*/
	/*BTNode<T> *p;
	if (node == NULL)
		node = new BTNode<T>(data);
	else if (data < node->data) {
		p = insert(data, node->left);
		p->parent = node;
	}
	else {
		p = insert(data, node->right);
		p->parent = node;
	}
	return node;*/
	BTNode<T> *p, *q = NULL;
	if (node == NULL) {
		node = new BTNode<T>(data);
		return node;
	}
	p = node;
	while (1) {
		if (data < p->data) {
			if (p->left == NULL) {
				q = new BTNode<T>(data, p);
				p->left = q;
				break;
			}
			else
				p = p->left;
		}
		else if (data >= p->data) {
			if (p->right == NULL) {
				q = new BTNode<T>(data, p);
				p->right = q;
				break;
			}
			else
				p = p->right;
		}
	}
	return	q;
}

template <class T>
BTNode<T>* BSTree<T>::get_max(BTNode<T> *node) {
	BTNode<T> *p = node;
	while (p->right != NULL)
		p = p->right;
	return p;
}

template <class T>
BTNode<T>* BSTree<T>::get_min(BTNode<T> *node) {
	BTNode<T> *p = node;
	while (p->left != NULL)
		p = p->left;
	return p;
}

template <class T>
BTNode<T>* BSTree<T>::predecessor(BTNode<T> *node) {
	if (node->left != NULL )
		return get_max(node->left);
	BTNode<T> *p = node->parent;
	while (p != NULL && node == p->left) {
		node = p;
		p->parent;
	}
	return p;
}

template <class T>
BTNode<T>* BSTree<T>::successor(BTNode<T> *node) {
	if (node->right != NULL)
		return get_min(node->right);
	BTNode<T> *p = node->parent;
	while (p != NULL && node == p->right) {
		node = p;
		p = p->parent;
	}
	return p;
}

template <class T>
void BSTree<T>::in_order() {
	/*if (root != NULL) {
		in_order(root->left);
		cout << root->data << endl;
		in_order(root->right);
	}*/
	stack<BTNode<T>*, vector<BTNode<T>*>> s;
	BTNode<T> *p = root;
	if (root != NULL) {
		while (!s.empty() || p != NULL) {
			if (p != NULL) {
				s.push(p);
				p = p->left;
				continue;
			}
			p = s.top();
			s.pop();
			cout << p->data << endl;
			p = p->right;
		}
	}
}

template <class T>
void BSTree<T>::pre_order() {
	/*if (root != NULL) {
		cout << root->data << endl;
		pre_order(root->left);
		pre_order(root->right);
	}*/
	stack<BTNode<T>*, vector<BTNode<T>*>> s;
	BTNode<T>* p = root;

	if (root != NULL) {
		while (!s.empty() || p != NULL) {
			if (p != NULL) {
				cout << p->data << endl;
				s.push(p);
				p = p->left;
				continue;
			}
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
}

template <class T>
void BSTree<T>::post_order() {
	/*if (root != NULL) {
		post_order(root->left);
		post_order(root->right);
		cout << root->data << endl;
	}*/
	if (root != NULL) {
		stack<BTNode<T>*, vector<BTNode<T>*>> s;
		stack<bool, vector<bool>> st;
		BTNode<T> *p = root;
		while (!s.empty() || p != NULL) {
			if (p != NULL) {
				s.push(p);
				p = p->left;
				st.push(false);
				continue;
			}
			while (!st.empty() && st.top()) {
				p = s.top();
				cout << p->data << endl;
				s.pop(); st.pop();
			}
			if (st.empty())
				break;
			p = s.top(); 
			st.pop(); 
			st.push(true); 
			p = p->right;
		}
	}
}

template <class T>
void BSTree<T>::layer_order() {
	BTNode<T> *p;
	queue<BTNode<T>*, list<BTNode<T>*>> q;

	if (root != NULL) {
		p = root;
		q.push(p);
		while (!q.empty()) {
			p = q.front();
			q.pop();
			cout << p->data << endl;
			if (p->left != NULL)
				q.push(p->left);
			if (p->right != NULL)
				q.push(p->right);
		}
	}
}

template <class T>
void BSTree<T>::remove(const T &data) {
	BTNode<T> *p, *q, *node = search(data, root);
	if (node->left == NULL || node->right == NULL)
		p = node;
	else
		p = successor(node);
	if (p->left != NULL)
		q = p->left;
	else
		q = p->right;
	if (q != NULL)
		q->parent = p->parent;
	if (p->parent == NULL)
		q = root;
	else if (p->parent->left == p)
		p->parent->left = q;
	else
		p->parent->right = q;
	if (p != node)
		node->data = p->data;
	delete p;
}

template <class T>
int BSTree<T>::depth(BTNode<T> *node) {
	/*if (node == NULL)
		return 1;
	int l = depth(node->left);
	int r = depth(node->right);
	return (l > r) ? (l + 1): (r + 1);*/
	stack<BTNode<T> *, vector<BTNode<T> *>> s1;
	stack<int, vector<int>> s2;
	BTNode<T> *p = node;
	int cur_depth = 1, max_depth = 0;;

	if (node != NULL) {
		while (!s1.empty() || p != NULL) {
			if (p != NULL) {
				s1.push(p);
				p = p->left;
				s2.push(cur_depth++);
				continue;
			}
			p = s1.top();
			s1.pop();
			cur_depth = s2.top();
			s2.pop();
			if (p->left == NULL && p->right == NULL)
				if (max_depth < cur_depth)
					max_depth = cur_depth;
			p = p->right;
			cur_depth++;
		}
	}
	return max_depth;
}

template <class T>
int BSTree<T>::depth() {
	return depth(root);
}

#endif