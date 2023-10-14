// Source: https://oj.leetcode.com/problems/integer-to-roman/

class Solution {
public:
    string intToRoman(int num) {
        const char *s[4][10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
                                "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
                                "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
                                "", "M", "MM", "MMM", "",   "",  "",   "",    "",     ""};
        string ans;
        for (int i = 0; num != 0; i++)
            ans = s[i][num % 10] + ans, num /= 10 ;
        return ans;
    }
};