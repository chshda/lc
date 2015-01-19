// Source: https://oj.leetcode.com/problems/unique-binary-search-trees/

class Solution {
public:
    int numTrees(int n) { //DP
        vector<int> v(n+1);
        v[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            v[i] = 0;
            for (int j = 1; j <= i; j++) //枚举根节点
                v[i] += v[j-1] * v[i-j];
        }
        return v[n];
    }
};