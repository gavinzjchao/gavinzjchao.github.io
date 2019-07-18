bool searchMatrix(vector<vector<int>>& matrix, int target) {
  if (matrix.empty() || matrix[0].empty())
    return false;

  // look up upper bound from matrix[0 -> m -1, 0]
  int pivot = binary_search_lower_bound(matrix, target);
  // small than the matrix's fitst element
  if (pivot < 0)
    return false;

  // if find target just in matrix[0 -> m- 1, 0] mark it as -1, early stop searching
  if (pivot == matrix.size())
    return true;

  // find position in matrix[pivot - 1, 0 -> n - 1]
  return binary_search(matrix[pivot], target);
}

int binary_search_lower_bound(vector<vector<int>> &matrix, int target) {
  int b = 0, e = matrix.size() - 1, mid;
  while (b <= e) {
    mid = b + (e - b) / 2;
    int cur = matrix[mid][0];
    if (cur == target)
      return matrix.size();
    else if (cur > target) {
      e = mid - 1;
    } else {
      b = mid + 1;
    }
  }

  return e;
}

bool binary_search(vector<int> &nums, int target) {
  int b = 0, e = nums.size() - 1, mid;
  while (b <= e) {
    mid = b + (e - b) / 2;
    if (nums[mid] == target) {
      return true;
    } else if (nums[mid] < target) {
      b = mid + 1;
    } else {
      e = mid - 1;
    }
  }

  return false;
}
