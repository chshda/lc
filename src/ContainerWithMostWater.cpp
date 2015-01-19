// Source: https://oj.leetcode.com/problems/container-with-most-water/

class Solution {
public:
    int maxArea(vector<int> &height) {
        int st = 0, ed = height.size() - 1, ans = 0;
        while (st < ed) //两端向中间移动
        {
            ans = max(ans, min(height[st], height[ed]) * (ed - st));
            if (height[st] <= height[ed]) st++; //替换掉较短的一根
            else ed--;
        }
        return ans;
    }
};