vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> res(1, vector<int>());

	for (int i = 0; i < nums.size(); i++) {
		vector<int> cur;
		cur.push_back(nums[i]);
		res.push_back(cur);
		dfs(nums, i + 1, cur, res);
	}

	return res;

}


void dfs(vector<int> &nums, int pos, vector<int> &cur, vector<vector<int>> &res) {
	if (pos >= nums.size())
		return;

	dfs(nums, pos + 1, cur, res);
	cur.push_back(nums[pos]);
	res.push_back(cur);
	dfs(nums, pos + 1, cur, res);
	cur.pop_back();

}
/*
Output
[[],[1],[1,3],[1,2],[1,2,3],[2],[2,3]]
Expected
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
*/
