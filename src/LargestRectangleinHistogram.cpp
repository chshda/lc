// Source: https://oj.leetcode.com/problems/largest-rectangle-in-histogram/

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        height.push_back(0);
        stack<int> s;
        int i = 0, ans = 0;
        while (i < height.size())
        {
            if (s.empty() || height[s.top()] <= height[i])
                s.push(i++); //入栈过程，i递增
            else
            {
                int t = s.top(); s.pop(); //出栈过程，i不变
                ans = max(ans, height[t] * (s.empty() ? i : i - s.top() - 1));
            }
        }
        return ans;
    }
};