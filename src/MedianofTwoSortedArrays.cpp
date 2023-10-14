// Source: https://oj.leetcode.com/problems/median-of-two-sorted-arrays/

class Solution {
public:
    int f(int A[], int m, int B[], int n, int k)
    {
        if (m > n) return f(B, n, A, m, k); //A较短
        
        if (m == 0) return B[k-1];
        if (k == 1) return min(A[0], B[0]);
        
        int l1 = min(m, k / 2), l2 = k - l1;
        if (A[l1-1] == B[l2-1]) return A[l1-1];
        else if (A[l1-1] < B[l2-1]) return f(A+l1, m-l1, B, n, k-l1); //B较大，去掉A的一半
        else return f(A, m, B+l2, n-l2, k-l2);                        //A较大，去掉B的一半
    }
    
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        int x = m + n;
        if (x & 1) //奇数长度
            return f(A, m, B, n, x / 2 + 1);
        else       //偶数长度
            return (f(A, m, B, n, x / 2) + f(A, m, B, n, x / 2 + 1)) / 2.0;
    }
};