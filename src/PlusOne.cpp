// Source: https://oj.leetcode.com/problems/plus-one/

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        vector<int> ans;
        int carry = 1; //进位，初始的1表示加1
        for (int i = digits.size()-1; i >= 0; i--)
            ans.push_back((digits[i]+carry)%10), carry = (digits[i]+carry)/10;
        if (carry) ans.push_back(1);
        reverse(ans.begin(), ans.end()); //翻转，高位在前
        return ans;
    }
};