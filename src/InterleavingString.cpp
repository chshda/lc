// Source: https://oj.leetcode.com/problems/interleaving-string/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) { //DP
        bool dp[1000][1000] = {0};
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        
        if (n1 + n2 != n3) return 0;
        
        dp[0][0] = s3.empty() ? 1 : 0;
        
        for (int i = 1; i <= min(n1, n3); i++)
            if (s1[i-1] == s3[i-1]) dp[i][0] = 1;
            else break;
        
        for (int i = 1; i <= min(n2, n3); i++)
            if (s2[i-1] == s3[i-1]) dp[0][i] = 1;
            else break;
        
        for (int i = 1; i <= n1; i++)
            for (int j = 1; j <= n2; j++)
            {
                dp[i][j] = 0;
                int ti = i-1, tj = j-1, tk = i+j-1;
                if (s1[ti] == s3[tk]) dp[i][j] |= dp[i-1][j];
                if (s2[tj] == s3[tk]) dp[i][j] |= dp[i][j-1];
            }
        return dp[n1][n2];
    }
};