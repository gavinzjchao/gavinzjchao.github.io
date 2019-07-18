
void shuffle(vector<int> &nums) {
	int n = nums.size() - 1;
	while (n > 0) {
		int j = rand() % (n + 1);
		swap(nums[j], nums[n--]);
	}
}
