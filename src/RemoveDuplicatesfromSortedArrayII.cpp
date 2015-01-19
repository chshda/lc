// Source: https://oj.leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int id = -1, cnt = 0; //当前答案的下标，前一个元素出现的次数
        for (int i = 0; i < n; i++)
        {
            if (id == -1 || A[i] != A[id])
                A[++id] = A[i], cnt = 1;
            else if (cnt < 2) //相同时出现次数小于2才输出
                A[++id] = A[i], cnt++;
        }
        return id + 1;
    }
};