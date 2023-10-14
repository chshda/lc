// Source: https://oj.leetcode.com/problems/divide-two-integers/

class Solution {
public:
    int divide(int dividend, int divisor) {
        bool neg = (dividend>0 && divisor<0) || (dividend<0 && divisor>0); //记录结果的正负
        long long a = abs((long long)dividend), b = abs((long long)divisor), ans = 0; //转成正数
        while (a >= b)
        {
            long long t = b, cnt = 1;
            while (t < a) t <<= 1, cnt <<= 1; //左移直到除数大于被除数再减
            if (t > a) t >>= 1, cnt >>= 1;
            a -= t, ans += cnt;
        }
        ans = neg ? -ans : ans;
        return ans > INT_MAX ? INT_MAX : ans; //判断溢出
    }
};