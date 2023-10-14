// Source: https://oj.leetcode.com/problems/search-in-rotated-sorted-array/

class Solution {
public:
    int search(int A[], int n, int target) {
        if (n <= 0) return false;

        int st = 0, ed = n - 1;
        while (st <= ed)
        {
            int mid = st + ((ed - st) >> 1);
            if (target == A[mid]) return mid;//找到
           
            if (A[mid] >= A[st]) //中间点在左半段
            {
                if (target >= A[st] && target < A[mid]) ed = mid - 1; //target在mid左边
                else st = mid + 1;
            }
            else                //中间点在右半段
            {
                if (target <= A[ed] && target > A[mid]) st = mid + 1; //target在mid右边
                else ed = mid - 1;
            }
        }
        return -1;
    }
};