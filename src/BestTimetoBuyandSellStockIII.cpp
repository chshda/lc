// Source: https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

class Solution {
public:
    int maxProfit(vector<int> &prices) { //DP
        int n = prices.size();
        if (n == 0) return 0;
        
        vector<int> dpl(n, 0), dpr(n, 0);
        for (int i = 1, mn = prices[0]; i < n; i++) //左边
            dpl[i] = max(dpl[i-1], prices[i] - mn), mn = min(mn, prices[i]);
        for (int i = n-2, mx = prices[n-1]; i >= 0; i--) //右边
            dpr[i] = max(dpr[i+1], mx - prices[i]), mx = max(mx, prices[i]);
        
        int ans = dpr[0];
        for (int i = 1; i < n; i++)
            ans = max(ans, dpl[i-1] + dpr[i]);
        return ans;
    }
};