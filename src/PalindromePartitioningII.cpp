// Source: https://oj.leetcode.com/problems/palindrome-partitioning-ii/

class Solution {
public:
    int minCut(string s) { //DP
        if (s.empty()) return 0;
        
        int n = s.size();
        vector<int> dp(n + 1, INT_MAX);
        vector<vector<bool>> is(n, vector<bool>(n, 0));
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                if (s[i] == s[j] && (j - i <= 2 || is[i+1][j-1]))
                    is[i][j] = 1, dp[i] = min(dp[i], 1 + dp[j+1]);
        return dp[0] - 1;
    }
};