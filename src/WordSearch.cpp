// Source: https://oj.leetcode.com/problems/word-search/

class Solution {
public:
    int n, m;
    int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0}; //四个方向移动的增量
    
    bool dfs(int x, int y, int id, vector<vector<bool>> &vs, vector<vector<char> > &board, string &word)
    { //当前的行，列，单词下标，已访问的数组，二维数组，单词
        if (id == word.size()) return true;  //已找到
        
        for (int i = 0; i < 4; ++i)
        {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx >= 0 && tx < n && ty >= 0 && ty < m && !vs[tx][ty] && board[tx][ty] == word[id])
            { //未超出边界，未访问，且字母匹配
                vs[tx][ty] = true;
                if (dfs(tx, ty, id+1, vs, board, word)) return true;
                vs[tx][ty] = false; //回溯
            }
        }
        return false;
    }
    bool exist(vector<vector<char> > &board, string word) {
        if (word.empty()) return true;
        if (board.empty()) return false;
        n = board.size(), m = board[0].size();
        
        vector<vector<bool>> vs(n, vector<bool>(m, false));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (board[i][j] == word[0]) //首字母匹配
                {
                    vs[i][j] = true;
                    if (dfs(i, j, 1, vs, board, word)) return true;
                    vs[i][j] = false;
                }
            }
        return false;
    }
};