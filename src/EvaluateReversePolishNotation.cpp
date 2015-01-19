// Source: https://oj.leetcode.com/problems/evaluate-reverse-polish-notation/

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> s;
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i]=="+" || tokens[i]=="-" || tokens[i]=="*" || tokens[i]=="/")
            {
                int t1 = s.top(); s.pop();
                int t2 = s.top(); s.pop();
                if (tokens[i] == "+") s.push(t2 + t1);
                else if (tokens[i] == "-") s.push(t2 - t1);
                else if (tokens[i] == "*") s.push(t2 * t1);
                else s.push(t2 / t1);
            }
            else
            {
                int t;
                sscanf(const_cast<char *>(tokens[i].c_str()), "%d", &t);
                s.push(t);
            }
        }
        return s.top();
    }
};