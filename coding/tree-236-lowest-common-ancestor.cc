TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	// depth-first searching, 最近的满足left和right都被找到的root就是最小祖先
	if (!root || root == p || root == q)
		return root;

	TreeNode *left = lowestCommonAncestor(root->left, p, q);
	TreeNode *right = lowestCommonAncestor(root->right, p, q);

	if (left && right)
		return root;

	return left ? left : right;
}

