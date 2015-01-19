// Source: https://oj.leetcode.com/problems/surrounded-regions/

class Solution {
public:
    int m, n, dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
    stack<pair<int,int>> stk;
    
    void dfs(vector<vector<char>> &b, int x, int y)
    {
        /*递归爆栈
        b[x][y] = 'A';
        for (int i = 0; i < 4; i++)
        {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx >= 0 && tx < m && ty >= 0 && ty < n && b[tx][ty] == 'O')
                dfs(b, tx, ty);
        }*/
        
        stk.push(pair<int,int>(x, y));
        while (!stk.empty())
        {
            x = stk.top().first, y = stk.top().second; stk.pop();
            b[x][y] = 'A';
            for (int i = 0; i < 4; i++)
            {
                int tx = x + dx[i], ty = y + dy[i]; 
                if (tx >= 0 && tx < m && ty >= 0 && ty < n && b[tx][ty] == 'O')
                    stk.push(pair<int,int>(tx, ty));
            }
        }
    }

    void solve(vector<vector<char>> &b) {
        if (b.empty() || b[0].empty()) return;
        
        m = b.size(), n = b[0].size();
        for (int i = 0; i < n; i++)
        {
            if (b[0][i] == 'O') dfs(b, 0, i);
            if (b[m-1][i] == 'O') dfs(b, m-1, i);
        }
        for (int i = 1; i < m-1; i++)
        {
            if (b[i][0] == 'O') dfs(b, i, 0);
            if (b[i][n-1] == 'O') dfs(b, i, n-1);
        }
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (b[i][j] == 'A') b[i][j] = 'O';
                else if(b[i][j] == 'O') b[i][j] = 'X';
    }
};