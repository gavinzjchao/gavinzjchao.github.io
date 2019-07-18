/*
 * In:  1, 2, 3, 0, 2
 * Out: 3
 *
 * <1, 2>, [0, 2]
 * <0, 2>
 *
 * <1, 3>, [2, 2]
 *
 * <1, 2>, []
 *
 * buy, sell, rest
 *
 */

int maxProfit(vector<int> &prices) {
	if (prices.size() <= 1)
		return 0;

	return profit(prices, 0, prices.size() -1);
}

int profit(vector<int> &prices, int b, int e) {
	if (b >= e)
		return 0;

	int cur_min = INT_MAX;

	int gap = 0;
}
