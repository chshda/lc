// Source: https://oj.leetcode.com/problems/pascals-triangle/

class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > ans;
        for (int i = 0; i < numRows; i++)
        {
            vector<int> v;
            if (i == 0) v.push_back(1);
            else
            {
                for (int j = 0; j <= i; j++)
                    if (j == 0) v.push_back(1);
                    else if(j == i) v.push_back(1);
                    else v.push_back(ans[i-1][j-1] + ans[i-1][j]);
            }
            ans.push_back(v);
        }
        return ans;
    }
};