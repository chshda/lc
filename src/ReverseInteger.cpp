// Source: https://oj.leetcode.com/problems/reverse-integer/

class Solution {
public:
    int reverse(int x) {
        long long a = x; //防止溢出
        long long flag = 1, ans = 0; //记录负数
        if (a < 0) flag = -1, a = -a;
        while(a) ans = ans*10 + a%10, a /= 10;
        ans = flag * ans;
        return ans > INT_MAX  || ans < INT_MIN ? 0 : ans;
    }
};