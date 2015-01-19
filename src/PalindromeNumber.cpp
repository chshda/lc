// Source: https://oj.leetcode.com/problems/palindrome-number/

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return 0; //负数不可能回文
        if (x < 10) return 1;//一位数一定回文
        
        int q = 10;
        while (x / q > 9) q *= 10; 
        while (x)
        {
            if (x/q != x%10) return 0;
            x -= x / q * q; //减去最高位
            x /= 10;        //减去最低位
            q /= 100;
        }
        return 1;
    }
};