// Source: https://oj.leetcode.com/problems/single-number/

class Solution {
public:
    int singleNumber(int A[], int n) {
        int ans = 0;
        for (int i = 0; i < n; i++) ans ^= A[i];
        return ans;
    }
};