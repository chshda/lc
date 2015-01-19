// Source: https://oj.leetcode.com/problems/n-queens-ii/

class Solution {
public:
    const static int mx = 10000;
    bool vsy[mx], vsd1[2*mx], vsd2[2*mx]; //列、主对角线、副对角线是否已有皇后
    
    int dfs(int x, int n)
    { //当前行数，N大小
        if (x == n) return 1;
        
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (!vsy[i] && !vsd1[x+i] && !vsd2[n+x-i-1]) //列及两条对角线均没有皇后
            {
                vsy[i] = vsd1[x+i] = vsd2[n+x-i-1] = true;
                cnt += dfs(x+1, n);
                vsy[i] = vsd1[x+i] = vsd2[n+x-i-1] = false; //回溯
            }
        }
        return cnt;
    }
    int totalNQueens(int n) {
        return dfs(0, n);
    }
};