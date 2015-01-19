// Source: https://oj.leetcode.com/problems/first-missing-positive/

class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        if (n < 1) return 1; //没有元素，返回1
        
        for (int i = 0; i < n; )
        {
            if (A[i]<0 || A[i]>=n || A[i]==i+1 || A[i]==A[A[i]-1])
                i++; //非法数字或者数字位置正确
            else
                swap(A[i], A[A[i] - 1]);//交换到正确的位置上
        }
        
        for (int i = 0; i < n; i++)
            if (A[i] != i + 1) //位置不正确
                return i + 1;
        return n + 1; //全部位置正确
    }
};