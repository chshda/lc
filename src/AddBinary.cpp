// Source: https://oj.leetcode.com/problems/add-binary/

class Solution {
public:
    string addBinary(string a, string b) {
        if (a.length() < b.length()) a.swap(b);
        b = string(a.length()-b.length(), '0') + b; //添加前导0使二者一样长
        
        string sum(a.length(), '0');
        int carry = 0;//进位
        for (int i = a.length()-1, t; i >= 0; i--)
            t = (a[i]-'0')+(b[i]-'0')+carry, sum[i] = t%2+'0', carry = t/2;
        if (carry) sum = '1' + sum; //还有进位
        return sum;
    }
};