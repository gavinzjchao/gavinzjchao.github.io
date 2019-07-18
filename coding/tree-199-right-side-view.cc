vector<int> rightSideView(TreeNode* root) {
	vector<int> res;
	if (!root)
		return res;

	stack<pair<TreeNode*, int>> s;
	s.push(make_pair(root, 0));

	while (!s.empty()) {
		pair<TreeNode*, int> cur = s.top();
		s.pop();
		int level = cur.second;
		TreeNode *rt = cur.first;

		if (res.size() <= level)
			res.push_back(rt->val);
		else
			res[level] = rt->val;

		// first in last out; so first push rt->right into the stack
		if (rt->right)
			s.push(make_pair(rt->right, level + 1));

		if (rt->left)
			s.push(make_pair(rt->left, level + 1));

	}

	return res;
}
