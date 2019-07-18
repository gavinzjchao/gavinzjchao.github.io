int sumNumbers(TreeNode* root) {

	if (!root)
		return 0;

	int sum = 0;
	sum_nums(root, 0, sum);
	return sum;
}

void sum_nums(TreeNode *root, int cur_sum, int &total_sum) {
	if (!root)
		return;

	int update = 10 *cur_sum + root->val;
	if (!root->left && !root->right)
		total_sum += update;

	if (root->left)
		sum_nums(root->left, update, total_sum);

	if (root->right)
		sum_nums(root->right, update, total_sum);
}
