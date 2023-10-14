// Source: https://oj.leetcode.com/problems/sort-colors/

class Solution {
public:
    void sortColors2(int A[], int n) { //计数排序
        int a[3] = {0};
        for (int i = 0; i < n; i++) a[A[i]]++;
        for (int i = 1; i < 3; i++) a[i] += a[i-1];
        vector<int> B(n, 0);
        for (int i = 0; i < n; i++) B[--a[A[i]]] = A[i];
        for (int i = 0; i < n; i++) A[i] = B[i];
    }
    
    void sortColors(int A[], int n) { 
        int n1 = 0, n2 = 0, n3 = 0; //0 1 2出现的次数
        for (int i = 0; i < n; i++)
        {
            if (A[i] == 0) ++n1;
            else if(A[i] == 1) ++n2;
            else if (A[i] == 2) ++n3;
        }
        int i = 0;
        while (n1--) A[i++] = 0;
        while (n2--) A[i++] = 1;
        while (n3--) A[i++] = 2;
    }
};