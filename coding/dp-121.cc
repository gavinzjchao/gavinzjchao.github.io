/*
 * 7, 1, 5, 3, 6, 4
 *
 */
int maxProfit2(vector<int> &prices) {
	if (prices.size() <= 1)
		return 0;

	vector<int> dp(prices.size() + 1, INT_MAX);
	int gap = 0;
	for (int i = 1; i <= prices.size(); i++) {
		for (int j = 0; j < i; j++) {
			dp[i] = min(prices[i - 1], dp[j]);
			gap = max(gap, prices[i - 1] - dp[i]);
		}
	}

	return gap;
}

int maxProfit(vector<int> &prices) {
	if (prices.size() <= 1)
		return 0;

	int gap = 0;
	int cur_min = INT_MAX;
	for (int i = 0; i < prices.size(); i++) {
		gap = max(prices[i] - cur_min, gap);
		cur_min = min(prices[i], cur_min);
	}

	return gap;
}
