// Source: https://oj.leetcode.com/problems/implement-strstr/

class Solution {
public:
    int strStr(char *haystack, char *needle) { //KMP算法
        int l1 = strlen(haystack), l2 = strlen(needle), i = 0, j = 0;
        int next[100005]; getNext(needle, next);
        while (i < l1 && j < l2)
            if (j == -1 || haystack[i] == needle[j]) i++, j++;
            else j = next[j];
        if (j == l2) return i - l2;
        else return -1;
    }
    void getNext(char *t, int* next)
    {
        int l = strlen(t), i = 0, j = -1;
        next[0] = -1;
        while (i < l)
            if (j == -1 || t[i] == t[j]) next[++i] = ++j;
            else j = next[j];
        
    }
    
    int strStr2(char *haystack, char *needle) { //朴素算法
        int l1 = strlen(haystack), l2 = strlen(needle), i = 0, j = 0;
        while (i < l1 && j < l2)
            if (haystack[i] == needle[j]) i++, j++;
            else i -= j-1, j = 0;
        if (j == l2) return i - l2;
        else return -1;
    }
};