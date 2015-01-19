// Source: https://oj.leetcode.com/problems/valid-parentheses/

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (int i = 0; i < s.length(); i++)
            if (s[i]=='(' || s[i]=='[' || s[i]=='{')//×óÀ¨ºÅÈëÕ»
                st.push(s[i]);
            else if (!st.empty() && (st.top()==s[i]-1 || st.top()==s[i]-2))
                st.pop();   //ASCII¹ØÏµ£º)=(+1,]=[+2, }={+2
            else
                return false;
        return st.empty();
    }
};