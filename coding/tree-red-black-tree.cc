#include "tree-red-black-tree.h"

TreeNode *RedBlackTree::search(T v) {
	if (!m_root)
		return NULL;
	
	TreeNode *prev = NULL;
	TreeNode *cur = m_root;
	while (cur) {
		if (cur->val == v)
			return cur;
		else if (cur->val > v) {
			prev = cur;
			cur = cur->left;
		} else {
			prev = cur;
			cur = cur->right;
		}
	}

	return prev;
}

void RedBlackTree::same_direction_rotate(TreeNode *x,
		TreeNode *p, TreeNode *g, bool is_left_left) {
	// 1 swap color of parent and grand parent
	swap_color(p, g);

	// 2 relink tree structure
	if (is_left_left) {
		TreeNode *tmp = p->right;
		p->right = g;
		g->left = tmp;
	} else {
		TreeNode *tmp = p->left;
		p->left = g;
		g->right = tmp;
	}
}

void RedBlackTree::diffrent_direction_rotate(TreeNode *x, 
		TreeNode *p, TreeNode *g, bool is_left_right) {


}

void RedBlackTree::right_rotate(TreeNode *node) {

}

void RedBlackTree::fix_inserted_tree(TreeNode *node) {
	if (node == m_root) {
		m_root->color = BLACK;
		return;
	}

	TreeNode *parent = node->parent, *uncle = node->get_uncle();
	TreeNode *grand_parent = node->parent ? node->parent->parent : NULL;

	if (parent->color == BLACK)
		return;
	
	if (uncle && uncle->color == RED) { // red uncle recursive re-coloring

	} else { // rotate tree
		if (parent->on_left()) {
			if (node->on_left()) {// left left type

			} else { // left right type

			}
		} else {
			if (!node->on_left()) { // right right type

			}
			else { // right left type

			}
		}
	}
}

void RedBlackTree::fix_deleted_tree(TreeNode *node) {

}

void RedBlackTree::insert(T v) {
	TreeNode *node = new TreeNode(v);
	if (!m_root) {
		m_root = node;
		m_root->color = BLACK;
	} else {
		TreeNode *parent = search(v);

		// already exist just return
		if (parent->val == v)
			return;

		node->parent = parent;

		// 1. insert node based on BST
		parent->val > v ? parent->left = node : parent->right = node;

		// 2. fix rb-tree based on rotate strategy
		fix_inserted_tree(node);
	}

}
