// Source: https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock/

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int ans = 0;
        for (int i = 0, mn = (1<<30); i < prices.size(); i++)
        {
            mn = min(mn, prices[i]); 
            ans = max(ans, prices[i] - mn);
        }
        return ans;
    }
};