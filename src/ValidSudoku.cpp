// Source: https://oj.leetcode.com/problems/valid-sudoku/

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        bool row[10][10]={0}, col[10][10]={0}, mid[10][10]={0}; //行、列、九宫格
        for (int i = 0; i < 9; i++) //遍历每个元素，看其所属的行、列、九宫格是否合法
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.') continue;
                int x = board[i][j] - '1';
                if (row[i][x] || col[j][x] || mid[i/3*3+j/3][x]) return false;
                row[i][x] = col[j][x] = mid[i/3*3+j/3][x] = true;
            }
            return true;
    }
    
    bool isValidSudoku2(vector<vector<char> > &board) {
        for (int i = 0; i < 9; i++)
        {
            set<char> s; //检查每列
            for (int j = 0; j < 9; j++)
                if(board[i][j] == '.')
                    continue;
                else if(s.find(board[i][j]) != s.end())
                    return false;
                else 
                    s.insert(board[i][j]);
            
            s.clear(); //检查每行
            for (int j = 0; j < 9; j++)
                if(board[j][i] == '.')
                    continue;
                else if(s.find(board[j][i]) != s.end())
                    return false;
                else 
                    s.insert(board[j][i]);
            
            s.clear(); //检查每个小九宫格
            int x = i/3*3, y = i%3*3;
            for (int j = x; j < x+3; j++)
                for (int k = y; k < y+3; k++)
                    if(board[j][k] == '.')
                        continue;   
                    else if(s.find(board[j][k]) != s.end())
                        return false;
                    else 
                        s.insert(board[j][k]);
        }
        return true;
    }
};