// Source: https://oj.leetcode.com/problems/unique-paths/

class Solution {
public:
    long long gcd(long long a, long long b)
    {
        for(long long t; t = a % b; a = b, b = t);
        return b;
    }
    int uniquePaths(int m, int n) { //组合数
        m--, n--;
        if (m < n) swap(m, n);
        m += n;
        long long a = 1, b = 1;
        for (int i = 0; i < n; i++)
        {
            a *= m - i, b *= n - i;
            long long g = gcd(a, b);
            a /= g, b /= g;
        }
        return a / b;
    }
};