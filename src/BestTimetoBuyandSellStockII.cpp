// Source: https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int ans = 0;
        for (int i = 1, st = 0; i < prices.size(); i++)
        {
            if (prices[i] < prices[i-1]) //价格下降
                ans += prices[i-1] - prices[st], st = i;
            else if(i == prices.size() - 1) //到达最后
                ans += prices[i] - prices[st];
        }
        return ans;
    }
};