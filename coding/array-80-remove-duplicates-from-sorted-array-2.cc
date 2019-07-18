int removeDuplicates(vector<int>& nums) {
	if (nums.size() <= 2)
		return nums.size();

	int b = 0, e = 1, c = 0;
	while (e < nums.size()) {
		if (nums[e] == nums[b]) {
			if (c >= 1) {
				e++;
			}
			else {
				swap(nums[e++], nums[++b]);
				c++;
			}
		} else {
			c = 0;
			swap(nums[e++], nums[++b]);
		}
	}

	return b + 1;
}
