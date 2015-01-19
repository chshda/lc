// Source: https://oj.leetcode.com/problems/spiral-matrix-ii/

class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int>> v(n, vector<int>(n)); //一定是正方形，比矩形情况简单
        for (int i = 0, cnt = 1, d = n; i <= (n - 1)/ 2; i++, d -= 2)
        {
            int x = i, y = i;
            for (int i = 0; i < d; i++) v[x][y+i] = cnt++;
            y += d - 1;
            for (int i = 1; i < d; i++) v[x+i][y] = cnt++;
            x += d - 1;
            for (int i = 1; i < d; i++) v[x][y-i] = cnt++;
            y -= d - 1;
            for (int i = 1; i < d-1; i++) v[x-i][y] = cnt++;
        }
        return v;
    }
};