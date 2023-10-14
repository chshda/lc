// Source: https://oj.leetcode.com/problems/count-and-say/

class Solution
{
public:
    string next(string s)
    {
        stringstream ss;
        int count = 1;
        char cur = s[0];
        
        for (int i = 1; i < s.length(); i++)
            if(s[i] == cur)
                count ++;
            else
            {
                ss << count << cur;
                count = 1, cur = s[i];
            }
        ss << count << cur;
        return ss.str();
    }
    
    string countAndSay(int n)
    {
        string s = "1";
        while (--n) s = next(s); //重复n-1次
        return s;
    }
};