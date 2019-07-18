int findKthLargest(vector<int>& nums, int k) {
	if (nums.empty() || k <= 0 || k > nums.size())
		return -1;

	int beg = 0, end = nums.size();

	while (beg < end) {
		int pivot = partition(nums, beg, end);
		if (pivot == k - 1)
			return nums[pivot];
		else if (pivot > k - 1) {
			right = pivot;
		} else {
			left = pivot + 1;
		}
	}
}


int partition(vector<int> &nums, int beg, int end) {
	int pivot = nums[beg];
	
	int big = beg, small = beg + 1;
	while (small < end) {
		if (nums[small] > pivot) {
			swap(nums[++big], nums[small]);
		}
		small++;
	}
	swap(nums[big], nums[beg]);

	return big;
}

/*
int partition(vector<int> &nums, int beg, int end) {
	int pivot = nums[beg];

	int small = beg, big = beg + 1;
	while (big < end) {
		if (nums[big] < pivot) {
			swap(nums[++small], nums[big]);
		}
		big++;
	}

	swap(nums[beg], nums[small]);
	return small;
}
*/
