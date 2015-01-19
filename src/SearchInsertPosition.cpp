// Source: https://oj.leetcode.com/problems/search-insert-position/

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        if (target > A[n-1]) return n;
        
        int st = 0, ed = n - 1;
        while (st < ed)
        {
            int mid = st + (ed - st) / 2;
            if (A[mid] >= target) ed = mid; //大于或等于
            else st = mid + 1;
        }
        return st;
    }
};