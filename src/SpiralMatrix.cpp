// Source: https://oj.leetcode.com/problems/spiral-matrix/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        vector<int> ans;
        if (matrix.empty() || matrix[0].empty()) return ans;
        
        int m = matrix.size(), n = matrix[0].size(); //行数、列数
        for (int i = 0, dx = m, dy = n; i <= min((m-1)/2, (n-1)/2); ++i, dx -= 2, dy -= 2) //逐环进行
        {
            int x = i, y = i; //起点坐标
            for (int j = 0; j < dy; j++) ans.push_back(matrix[x][y+j]); //向右走
            y += dy - 1;
            for (int j = 1; j < dx; j++) ans.push_back(matrix[x+j][y]); //向下走
            x += dx - 1;
            if (dx > 1) //行数大于2才要往回走
            {
                for (int j = 1; j < dy; j++) ans.push_back(matrix[x][y-j]); //向左走
                y -= dy - 1;
            }
            if (dy > 1) //列数大于2才要往回走
            {
                for (int j = 1; j < dx-1; j++) ans.push_back(matrix[x-j][y]); //向上走
            }
        }
        return ans;
    }
};