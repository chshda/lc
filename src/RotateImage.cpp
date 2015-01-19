// Source: https://oj.leetcode.com/problems/rotate-image/

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        for (int i = 0, len = n; i < (n + 1) / 2; i++, len -= 2) //逐环进行
        {
            int x = i, y = i;
            for (int j = 0; j < len - 1; j++)
            {
                int tem = matrix[x][y+j];
                matrix[x][y+j] = matrix[x+len-1-j][y];
                matrix[x+len-1-j][y] = matrix[x+len-1][y+len-1-j];
                matrix[x+len-1][y+len-1-j] = matrix[x+j][y+len-1];
                matrix[x+j][y+len-1] = tem;
            }
        }
    }
};