// Source: https://oj.leetcode.com/problems/maximum-product-subarray/

class Solution {
public:
    int maxProduct(int A[], int n) {
        int mx = A[0], mn = A[0], ans = A[0], tmx, tmn;
        for (int i = 1; i < n; i++)
            tmx = mx, tmn = mn,
            mx = max(A[i], max(tmx*A[i], tmn*A[i])), 
            mn = min(A[i], min(tmx*A[i], tmn*A[i])),
            ans = max(ans, mx);
        return ans;
    }
};