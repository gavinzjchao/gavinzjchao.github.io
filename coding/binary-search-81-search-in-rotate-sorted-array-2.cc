bool search(vector<int>& nums, int target) {
	if (nums.empty())
		return false;

	int b = 0,  e = nums.size() - 1, mid;
	while (b <= e) {
		mid = b + (e - b) / 2;
		if (nums[mid] == target)
			return true;
		else if (nums[mid] > target) {
			if (nums[mid] > nums[e]) {
				e = mid - 1;
			} else {
				b = mid + 1;
			}
		} else {
			if (nums[mid] >  nums[0]) {
				b = mid + 1;
			} else {
				e = mid - 1;
			}
		}
	}

	return false;
}

    int search(vector<int>& nums, int target) {
        if (nums.empty())
            return -1;

        int l = 0;
        int r = nums.size() - 1;
        int m;
        while (l <= r) {
            m = (l + r) / 2;

            if (nums[m] == target) {
                return m;
            } else if (target < nums[m]) {
                if (nums[m] > nums[r] && target <= nums[r]) {
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            } else {
                if (nums[m] < nums[l] && target >= nums[l]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
        }
        return -1;
    }
