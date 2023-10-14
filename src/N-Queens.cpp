// Source: https://oj.leetcode.com/problems/n-queens/

class Solution {
public:
    vector<bool> vsy, vsd1, vsd2; //列、主对角线、副对角线是否已有皇后
    vector<int> cur; //cur[i]：第i行皇后的位置
    
    void dfs(int x, int n, vector<vector<string>> &ans)
    { //当前行数，N大小，答案
        if (x == n) //找到一组解
        {
            vector<string> tem;
            for (int i = 0; i < n; i++)
            {
                string s;
                if (cur[i] > 0) s += string(cur[i], '.');
                s += "Q";
                if (n-1-cur[i] > 0) s += string(n-1-cur[i], '.');
                tem.push_back(s);
            }
            ans.push_back(tem);
            return ;
        }
        
        for (int i = 0; i < n; i++)
        {
            if (!vsy[i] && !vsd1[x+i] && !vsd2[n+x-i-1]) //列及两条对角线均没有皇后
            {
                vsy[i] = vsd1[x+i] = vsd2[n+x-i-1] = true;
                cur[x] = i;
                dfs(x+1, n, ans);
                vsy[i] = vsd1[x+i] = vsd2[n+x-i-1] = false; //回溯
            }
        }
    }
    vector<vector<string> > solveNQueens(int n) {
        cur.resize(n);
        
        vsy.resize(n); //初始化vsy
        for (int i = 0; i < n; ++i)
            vsy[i] = false;
        
        vsd1.resize(2*n); //初始化vsd1和vsd2
        vsd2.resize(2*n);
        for (int i = 0; i < 2 * n; ++i)
            vsd1[i] = vsd2[i] = false;
        
        vector<vector<string> > ans;
        dfs(0, n, ans);
        return ans;
    }
};