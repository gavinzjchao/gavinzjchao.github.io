vector<int> preorderTraversal(TreeNode* root) {
	vector<int> res;
	if (!root)
		return res;

	stack<TreeNode*> s;
	s.push(root);

	while (!s.empty()) {
		TreeNode *cur = s.top();
		res.push_back(cur->val);
		s.pop();
		if (cur->right)
			s.push(cur->right);
		if (cur->left)
			s.push(cur->left);
	}

	return res;
}
