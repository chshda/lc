// Source: https://oj.leetcode.com/problems/set-matrix-zeroes/

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        
        int m = matrix.size(), n = matrix[0].size();
        bool row0 = false, col0 = false; //第一行和第一列是否需要置0
        for (int i = 0; i < n; i++) row0 |= matrix[0][i] == 0; //有一个0即需要全部置0
        for (int i = 0; i < m; i++) col0 |= matrix[i][0] == 0;
        
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0; //把该行和该列的第一个元素作为标记
        
        for (int i = 1; i < m; i++)
            if (matrix[i][0] == 0) //根据标记进行操作
                for (int j = 1; j < n; j++)
                    matrix[i][j] = 0;
                    
        for (int i = 1; i < n; i++)
            if (matrix[0][i] == 0) //根据标记进行操作
                for (int j = 1; j < m; j++)
                    matrix[j][i] = 0;
        
        if (row0) //第一行
            for (int i = 1; i < n; i++) 
                matrix[0][i] = 0;
        
        if (col0) //第一列
            for (int i = 1; i < m; i++)
                matrix[i][0]= 0;
    }
};