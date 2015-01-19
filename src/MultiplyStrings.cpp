// Source: https://oj.leetcode.com/problems/multiply-strings/

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        int l1 = num1.size(), l2 = num2.size();
        string ans(l1+l2, '0');
        
        for (int i = l1-1; i >= 0; i--)
        {
            int carry = 0; //进位
            for (int j = l2-1; j >= 0; j--)
            {
                int tem = (num1[i]-'0') * (num2[j]-'0') + ans[i+j+1]-'0' + carry;
                if (tem > 9)
                    ans[i+j+1] = tem%10 + '0', carry = tem / 10;
                else
                    ans[i+j+1] = tem + '0', carry = 0;
            }
            if (carry) ans[i] += carry;
        }
        
        return ans.substr(ans.find_first_not_of('0')); //移除前导0
    }
};