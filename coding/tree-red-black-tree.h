#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

enum COLOR {RED, BLACK};

/*
 * TreeNode 
 */
template<typename T>
class TreeNode {

public:
	TreeNode(){}
	TreeNode(T v): val(v), color(RED), left(NULL), right(NULL), parent(NULL) {}
	~TreeNode() {}

	bool on_left() {
		return this == parent->left;
	}

	TreeNode *get_uncle() {
		if (!parent || !parent->parent)
			return NULL;

		if (parent->on_left()) {
			return parent->parent->right;
		} else {
			return parent->parent->left;
		}
	}

	TreeNode *get_sibling() {
		if (!parent)
			return NULL;

		if (on_left()) {
			return parent->right;
		} else {
			return parent->left;
		}
	}

public:
	T val;
	COLOR color;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;

};

template<typename T>
class RedBlackTree {
public:
	RedBlackTree() {
		m_root = NULL;
	}

	~RedBlackTree() {}

	void insert(T v);
	void delete_by_value(T v);
	void delte_by_node(TreeNode *node);
	TreeNode *search(T v);
	TreeNode *get_max_node(); 
	T get_max_value();
	TreeNode *get_min_node(); 
	T get_min_value();

	TreeNode* get_root() {
		return m_root;
	}

	void print_inorder() {
		vector<T> res = inorder();
		for (auto &v: res) {
			std::cout << v << "\t" << std::endl;
		}
	}

	void print_level_order() {
		vector<T> res = level_order();
		for (auto &v: res) {
			std::cout << v << "\t" << std::endl;
		}
	}

	vector<T> inorder();
	vector<T> level_order();

private:
	void swap_color(TreeNode *n1, TreeNode *n2) {
		if (!n1 || !n2)
			return;

		COLOR tmp = n1->color;
		n1->color = n2->color;
		n2->color = tmp;
	}

	void swap_value(TreeNode *n1, TreeNode *n2) {
		if (!n1 || !n2)
			return;

		T tmp = n1->val;
		n1->val = n2->val;
		n2->val = tmp;
	}

	void right_rotate(TreeNode *node);
	void left_rotate(TreeNode *node);

	void same_direction_rotate(TreeNode *node, TreeNode *parent, TreeNode *grand_parent, bool is_left_left);
	void diffrent_direction_rotate(TreeNode*, TreeNode*, TreeNode*, bool);


	void fix_inserted_tree(TreeNode *node);

	void fix_deleted_tree(TreeNode *node);

private:
	TreeNode *m_root;
};

#endif

