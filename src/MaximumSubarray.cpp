// Source: https://oj.leetcode.com/problems/maximum-subarray/

class Solution {
public:
    int maxSubArray(int A[], int n) {
        if (n <= 0) return 0; //长度不足
        
        int ans = A[0], cur = A[0]; //答案，dp值
        for (int i = 1; i < n; i++)
            cur = cur > 0 ? cur + A[i] : A[i], ans = max(ans, cur);
            
        return ans;
    }
};