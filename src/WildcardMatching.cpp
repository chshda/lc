// Source: https://oj.leetcode.com/problems/wildcard-matching/

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int ls = strlen(s), lp = strlen(p);
        
        int cnt = 0; //统计p匹配字符的最小长度
        for (const char *i = p; *i; i++)
            if (*i != '*') cnt++;
        if (cnt > ls) return false;
        
        //dp[i][j]：s的前i个字符能否匹配p的前j个字符
        vector<vector<bool>> dp(ls + 1, vector<bool>(lp + 1, false));
        
        //初始化
        dp[0][0] = true;
        for (int i = 1; i <= lp; i++)
            dp[0][i] = p[i-1] == '*' && dp[0][i-1];

        for (int i = 1; i <= ls; i++)
            for (int j = 1; j <= lp; j++)
            {
                if (p[j-1] == '*') //*号可以匹配，也可以不匹配
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                else if (p[j-1] == '?' || s[i-1] == p[j-1]) //?号或者相等
                    dp[i][j] = dp[i-1][j-1];
            }
        return dp[ls][lp];
    }
};