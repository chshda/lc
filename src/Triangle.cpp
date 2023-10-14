// Source: https://oj.leetcode.com/problems/triangle/

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) { //DP
        vector<int> v(triangle.size()); //重复利用的数组
        for (int i = 0; i < triangle.size(); i++)
            for (int j = i; j >= 0; j--)
            {
                if (j == 0)      v[j] = v[0] + triangle[i][0];
                else if (j == i) v[j] = v[j-1] + triangle[i][j];
                else
                {
                    v[j] = min(v[j-1], v[j]) + triangle[i][j];
                }
            }
        return *min_element(v.begin(), v.end());
    }
};