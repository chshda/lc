// Source: https://oj.leetcode.com/problems/excel-sheet-column-title/

class Solution {
public:
    string convertToTitle(int n) {
        string ans;
        while (n)
        {
            n--;
            ans = char('A' + n % 26) + ans, n /= 26;
        }
        return ans;
    }
};