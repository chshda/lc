// Source: https://oj.leetcode.com/problems/restore-ip-addresses/

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;
        restoreIpAddresses(0, 0, "", s, ans);
        return ans;
    }
    void restoreIpAddresses(int x, int id, string cur, string &s, vector<string> &ans)
    {
        if (x == 4) //得到4个了
        {
            if (id == s.size())
                ans.push_back(cur); 
            return;
        }
        string tem;
        for (int i = id, num = 0; i < id+3 && i < s.size(); i++)
        {
            num = num * 10 + s[i] - '0';
            tem += s[i];
            if (num < 256)
                restoreIpAddresses(x+1, i+1, cur.empty() ? tem : cur+"."+tem, s, ans);
            if (num == 0)
                break;
        }
    }
};