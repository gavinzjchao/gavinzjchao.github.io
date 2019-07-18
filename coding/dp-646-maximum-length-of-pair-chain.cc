// (1, 2), (2, 3), (3, 4) -> 2 {(1, 2), (3, 4)}
int findLongestChain(vector<vector<int>>& pairs) {
	if (pairs.size() <= 1)
		return pairs.size();

	sort(pairs.begin(), pairs.end(), less<int>);

	using PAIR = pair<int, int>;
	vector<PAIR> dp(paris.size());

	for (int i = 1; i < pairs.size() - 1; i++) {
		dp[i] = make_pair(1, pairs[i - 1][1]);
	}

	// 不是很熟悉这种跨长度的问题， 需要重刷
	for (int len = 2; len <= pairs.size(); len++) {
		for (int i = 0; i <= pairs.size() - len; i++) {
			int j = i + len - 1;
			int tail = dp[j - 1].second;
			if (pairs[j][1] > tail) {
				dp[j] = make_pair(dp[j - 1].first + 1, pairs[j][1]);
			} else {
				dp[j] = make_pair(dp[j - 1].first, min(dp[j - 1].second, paris[j][1]));
			}
		}
	}

	return dp[0][pairs.size() - 1].first;

}
