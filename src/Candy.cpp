// Source: https://oj.leetcode.com/problems/candy/

class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        
        vector<int> v(n, 1);
        for (int i = 1; i < n; i++) //右比左大
            v[i] = ratings[i] > ratings[i-1] ? v[i-1] + 1 : 1;
        for (int i = n-2; i >= 0; i--) //左比右大
            v[i] = ratings[i]>ratings[i+1] && v[i] <= v[i+1] ? v[i+1]+1 : v[i];

        return accumulate(v.begin(), v.end(), 0);
    }
};