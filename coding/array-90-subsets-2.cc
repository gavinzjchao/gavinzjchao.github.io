vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	vector<vector<int>> res(1, vector<int>());

	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size();) {
		int cnt = 0;
		while (cnt + i < nums.size() && nums[cnt + i] == nums[i])
			cnt++;
		for (int j = 0; j < res.size(); j++) {
			vector<int> cur = res[j];
			for (int k = 0; k < cnt; k++) {
				cur.push_back(nums[i]);
				res.push_back(cur);
			}
		}

		i += cnt;
	}

	return res;
}


void

mathsam's avatar
mathsam
285
Last Edit: October 26, 2018 8:17 PM

40.1K VIEWS

To solve this problem, it is helpful to first think how many subsets are there. If there is no duplicate element, the answer is simply 2^n, where n is the number of elements. This is because you have two choices for each element, either putting it into the subset or not. So all subsets for this no-duplicate set can be easily constructed:
num of subset

(1 to 2^0) empty set is the first subset
(2^0+1 to 2^1) add the first element into subset from (1)
(2^1+1 to 2^2) add the second element into subset (1 to 2^1)
(2^2+1 to 2^3) add the third element into subset (1 to 2^2)
....
(2^(n-1)+1 to 2^n) add the nth element into subset(1 to 2^(n-1))
Then how many subsets are there if there are duplicate elements? We can treat duplicate element as a spacial element. For example, if we have duplicate elements (5, 5), instead of treating them as two elements that are duplicate, we can treat it as one special element 5, but this element has more than two choices: you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset. Therefore, we are given an array (a1, a2, a3, ..., an) with each of them appearing (k1, k2, k3, ..., kn) times, the number of subset is (k1+1)(k2+1)...(kn+1). We can easily see how to write down all the subsets similar to the approach above.

    class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > totalset = {{}};
        sort(S.begin(),S.end());
        for(int i=0; i<S.size();){
            int count = 0; // num of elements are the same
            while(count + i<S.size() && S[count+i]==S[i])  count++;
            int previousN = totalset.size();
            for(int k=0; k<previousN; k++){
                vector<int> instance = totalset[k];
                for(int j=0; j<count; j++){
                    instance.push_back(S[i]);
                    totalset.push_back(instance);
                }
            }
            i += count;
        }
        return totalset;
        }

		[]
 dfs(vector<int> &nums, int pos, vector<int> &cur, vector<vector<int>> &res) {
	if (pos >= nums.size())
		return;

		dfs(nums, pos + 1, cur, res);
		cur.push_back(nums[pos]);
		res.push_back(cur);
		dfs(nums, pos + 1, cur, res);
		cur.pop_back();
}

