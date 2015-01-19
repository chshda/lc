// Source: https://oj.leetcode.com/problems/letter-combinations-of-a-phone-number/

class Solution {
public:
    string s[10] = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        f(0, "", digits, ans);
        return ans;
    }
    void f(int x, string cur, string digits, vector<string> &ans)
    {
        if (x == digits.size()) //到达末尾
        {
            ans.push_back(cur);
            return;
        }
        int d = digits[x] - '0';
        for (int i = 0; i < s[d].size(); i++) //枚举所有可能的字母
        {
            f(x+1, cur+s[d][i], digits, ans);
        }
    }
};