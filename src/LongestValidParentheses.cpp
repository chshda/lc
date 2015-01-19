// Source: https://oj.leetcode.com/problems/longest-valid-parentheses/

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), ans = 0;
        vector<int> dp(n, 0); //dp[i]表示从i开始的最长合法括号序列
        for (int i = n - 2; i >= 0; i--)
        {
            if (s[i] == '(') //第一个括号必须为左括号
            {
                int j = i + dp[i+1] + 1; //匹配该左括号的位置
                if (j < n && s[j] == ')')//满足匹配
                {
                    dp[i] = dp[i+1] + 2; 
                    if (j + 1 < n) dp[i] += dp[j + 1]; //后面还有
                    ans = max(ans, dp[i]);
                }
            }
        }
        return ans;
    }
};