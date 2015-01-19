// Source: https://oj.leetcode.com/problems/pascals-triangle-ii/

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> ans;
        for (int i = 0; i <= rowIndex; i++)
            if (i == 0) ans.push_back(1);
            else
                for (int j = i; j > 0; j--)
                    if (j == i) ans.push_back(1);
                    else ans[j] += ans[j-1];
        return ans;
    }
};