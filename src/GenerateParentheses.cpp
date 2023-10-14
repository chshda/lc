// Source: https://oj.leetcode.com/problems/generate-parentheses/

class Solution {
public:
    void f(int x, int n1, int n2, vector<char> &s, vector<string> &ans, int n)
    {//当前位置，左括号剩余数量，右括号剩余数量，当前摆放方式，答案，括号的组数
        if (n1 == 0) //左括号剩余个数为0
        {
            string tem;
            for (int i = 0; i < x; i++) tem += s[i];
            for (int i = x; i < n; i++) tem += ')';
            ans.push_back(tem);
            return;
        }
        
        s[x] = '('; f(x+1, n1-1, n2, s, ans, n);    //放左括号
        if (n1 < n2) //剩余左右括号数量不等时才能添加右括号
        {
            s[x] = ')'; f(x+1, n1, n2-1, s, ans, n);//放右括号
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<char> s(2*n);
        vector<string> ans;
        f(0, n, n, s, ans, 2*n);
        return ans;
    }
};