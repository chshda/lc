// Source: https://oj.leetcode.com/problems/distinct-subsequences/

class Solution {
public:
    int numDistinct(string s, string t) { //DP
        int ls = s.size(), lt = t.size();
        vector<vector<int>> dp(ls+1, vector<int>(lt+1));
        
        for (int i = 0; i <= ls; i++) dp[i][lt] = 1;
        for (int i = 0; i <  lt; i++) dp[ls][i] = 0;
        
        for (int i = ls-1; i >= 0; i--)
            for (int j = lt-1; j >= 0; j--)
            {
                dp[i][j] = dp[i+1][j];
                if (s[i] == t[j]) dp[i][j] += dp[i+1][j+1]; //首字母匹配
            }
        return dp[0][0];
    }
};