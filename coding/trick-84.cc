class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
    	if (heights.empty())
    		return 0;

    	stack<int> s;
    	int max_area = 0;
    	heights.push_back(0);
    	for (int i = 0; i < heights.size(); i++) {
    		if (s.empty() || heights[s.top()] <= heights[i])
    			s.push(i);
    		else {
    			while (!s.empty() && heights[i] < heights[s.top()]) {
    				int cur = s.top();
    				s.pop();
    				int area = heights[cur] * (s.empty() ? i : (i - s.top() - 1));
    				max_area = max(area, max_area);
    			}
    			s.push(i);
    		}
    	}

    	return max_area;
    }
};