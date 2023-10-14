// Source: https://oj.leetcode.com/problems/remove-duplicates-from-sorted-array/

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n == 0) return 0;
        
        int last = 0;
        for (int i = 1; i < n; i++)
            if (A[i] != A[last]) //新元素
                A[++last] = A[i];//插入到末尾
        return last + 1;
    }
};