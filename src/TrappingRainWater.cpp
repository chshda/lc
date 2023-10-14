// Source: https://oj.leetcode.com/problems/trapping-rain-water/

class Solution {
public:
    int trap(int A[], int n) {
        if (n <= 1) return 0;
        
        int mxid = 0; //最高柱子的位置
        for (int i = 1; i < n; i++)
            if (A[i] > A[mxid]) 
                mxid = i;
        
        int ans = 0; 
        for (int i = 1, mx = A[0]; i < mxid; i++)//左边情况
        {
            if (A[i] > mx) //当前最高的
                mx = A[i];
            else
                ans += mx - A[i]; //不是最高的，可以装与最高柱子高度差的水
        }
        
        for (int i = n-2, mx = A[n-1]; i > mxid; i--)//右边情况
        {
            if (A[i] > mx) 
                mx = A[i];
            else
                ans += mx - A[i];
        }
        
        return ans;
    }
};