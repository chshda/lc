// Source: https://oj.leetcode.com/problems/climbing-stairs/

class Solution {
public:
    int climbStairs(int n) { //斐波那契数列
        if (n <= 2) return n;
        int a = 1, b = 2, c;
        for (int i = 3; i <= n; i++)
            c = a + b, a = b, b = c;
        return b;
    }
};