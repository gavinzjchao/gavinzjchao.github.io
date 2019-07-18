int kthSmallest(TreeNode* root, int k) {
	// in-order k-th TreeNode is the k-th smallest number
	if (!root || k <= 0)
		return 0;

	TreeNode *cur = root;
	stack<TreeNode*> s;

	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->left;
		}

		cur = s.top();
		s.pop();
		if (k == 1)
			return cur->val;
		else
			k--;

		// 这里很容易出错，要记得一定置cur = cur->right否则会出现重复压栈的情况
		cur = cur->right;
	}

	return 0;
}
