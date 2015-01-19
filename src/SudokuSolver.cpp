// Source: https://oj.leetcode.com/problems/sudoku-solver/

class Solution {
public:
    bool dfs(int x, vector<vector<char> > &b)
    {
        if (x == 81) return true; //填完了
        int r = x / 9, c = x % 9;
        if (b[r][c] != '.') return dfs(x + 1, b);
        
        bool used[11] = {0};//每个数字是否使用过
        for (int i = 0; i < 9; i++)
        {
            if (b[r][i] != '.') used[b[r][i]-'0'] = 1; //行
            if (b[i][c] != '.') used[b[i][c]-'0'] = 1; //列
        }
        
        int tx = r / 3 * 3, ty = c / 3 * 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[tx+i][ty+j] != '.') //九宫格
                    used[b[tx+i][ty+j]-'0'] = 1;
                
        for (int i = 1; i <= 9; i++)
            if (!used[i])
            {
                b[r][c] = char(i + '0');
                if (dfs(x+1, b)) return true;
                // b[r][c] = '.';
            }
        return false;
    }
    
    void solveSudoku(vector<vector<char> > &board) {
        dfs(0, board);
    }
};