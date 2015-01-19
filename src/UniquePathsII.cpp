// Source: https://oj.leetcode.com/problems/unique-paths-ii/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &v) { //DP
        if (v.empty() || v[0].empty()) return 0;
        
        int m = v.size(), n = v[0].size();
        if (v[0][0] == 1 || v[m-1][n-1] == 1) return 0;
        
        vector<vector<int>> dp(m, vector<int>(n, 0)); //初始化为0
        for (int i = m-1; i >= 0; i--)
            for (int j = n-1; j >= 0; j--)
            {
                if (v[i][j] == 1) continue; //有障碍物
                
                if (i == m-1 && j == n-1) dp[i][j] = 1; //边界上
                else
                {
                    if (i+1 < m && v[i+1][j] == 0) dp[i][j] += dp[i+1][j];
                    if (j+1 < n && v[i][j+1] == 0) dp[i][j] += dp[i][j+1];
                }
            }
        return dp[0][0];
    }
};