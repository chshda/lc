// Source: https://oj.leetcode.com/problems/powx-n/

class Solution {
public:
    double pow(double x, int n) { //二分快速幂
        bool neg = 0;
        unsigned int exp = n; //unsigned, -2147483648取反后int溢出
        if (n < 0) exp = -n, neg = 1;
        
        double ans = 1, q = x;
        while (exp)
        {
            if (exp & 1) ans *= q;
            exp >>= 1, q = q * q;
        }
        
        return neg ? 1.0/ans : ans;
    }
};