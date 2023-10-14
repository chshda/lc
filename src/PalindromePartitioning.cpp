// Source: https://oj.leetcode.com/problems/palindrome-partitioning/

class Solution {
public:
    void f(int x, vector<string> &cur, vector<vector<string>> &ans, string &s)
    {
        if (x == s.size())
        {
            ans.push_back(cur); return;
        }
        for (int i = x; i < s.size(); i++) //枚举终点
        {
            bool is = 1; //是否回文
            for (int j = x, k = i; j < k; j++, k--)
                if (s[j] != s[k])
                {
                    is = 0; break;
                }
            if (is)
            {
                cur.push_back(s.substr(x, i-x+1));
                f(i+1, cur, ans, s);
                cur.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<string> cur;
        vector<vector<string>> ans;
        f(0, cur, ans, s);
        return ans;
    }
};