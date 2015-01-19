// Source: https://oj.leetcode.com/problems/merge-sorted-array/

class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        //从后往前归并
        for (int ia = m-1, ib = n-1, i = m+n-1; ;)
        {
            if (ib < 0) break;
            else if (ia < 0) A[i--] = B[ib--];
            else if (A[ia] > B[ib]) A[i--] = A[ia--];
            else A[i--] = B[ib--];
        }
    }
};