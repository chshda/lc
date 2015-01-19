// Source: https://oj.leetcode.com/problems/dungeon-game/

class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        if (dungeon.empty() || dungeon[0].empty()) return -1;
        
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0)); //从位置(i,j)开始最少的体力
        
        dp[m-1][n-1] = (dungeon[m-1][n-1] >= 0) ? 1 : (1 - dungeon[m-1][n-1]);
        for (int i = m - 2; i >= 0; i--)
            dp[i][n-1] = (dp[i+1][n-1] - dungeon[i][n-1] <= 0) ? 1 : (dp[i+1][n-1] - dungeon[i][n-1]);
        for (int i = n - 2; i >= 0; i--)
            dp[m-1][i] = (dp[m-1][i+1] - dungeon[m-1][i] <= 0) ? 1 : (dp[m-1][i+1] - dungeon[m-1][i]);
        
        for (int i = m - 2; i >= 0; --i)
            for (int j = n - 2; j >= 0; --j)
            {
                int t1 = (dp[i+1][j] - dungeon[i][j] <= 0) ? 1 : (dp[i+1][j] - dungeon[i][j]);
                int t2 = (dp[i][j+1] - dungeon[i][j] <= 0) ? 1 : (dp[i][j+1] - dungeon[i][j]);
                dp[i][j] = min(t1, t2);
            }
        return dp[0][0];
    }
};