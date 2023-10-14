// Source: https://oj.leetcode.com/problems/edit-distance/

class Solution {
public:
    int minDistance(string word1, string word2) { //DP
        int dp[1000][1000]; //dp[i][j：word1的前i个字符和word2的前j个字符的edit distance
        
        int n1 = word1.size(), n2 = word2.size();
        for (int i = 0; i <= n1; i++) dp[i][0] = i; //初始化
        for (int i = 0; i <= n2; i++) dp[0][i] = i;
        
        for (int i = 1; i <= n1; i++)
            for (int j = 1; j <= n2; j++)
            {
                if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]) + 1;
            }
        
        return dp[n1][n2];
    }
};