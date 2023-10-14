// Source: https://oj.leetcode.com/problems/maximal-rectangle/

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) { //转化为直方图问题，O(n^2)
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int m = matrix.size(), n  = matrix[0].size(), ans = 0;
        vector<int> v(n + 1, 0);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++) v[j] = matrix[i][j] == '0' ? 0 : v[j] + 1;
            
            stack<int> s;
            int k = 0;
            while (k < n + 1)
            {
                if (s.empty() || v[s.top()] <= v[k])
                    s.push(k++);
                else
                {
                    int t = s.top(); s.pop();
                    ans = max(ans, v[t] * (s.empty() ? k : k - s.top() - 1));
                }
            }
        }
        return ans;
    }

    int maximalRectangle2(vector<vector<char> > &matrix) { //转化为最大子矩阵和，O(n^3)
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int m = matrix.size(), n  = matrix[0].size();
        
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            vector<int> v(n, 0);
            for (int j = i; j < m; j++)
            {
                for (int k = 0; k < n; k++)
                    v[k] += matrix[j][k] - '0' == 0 ? -1000 : 1;
                
                int cur = 0;
                for (int k = 0; k < n; k++)
                {
                    if (cur >= 0) cur += v[k];
                    else cur = v[k];
                    ans = max(ans, cur);
                }
            }
        }
        return ans;
    }
};