// Source: https://oj.leetcode.com/problems/word-break-ii/

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict)
    {
        bool dp[10005] = {0};
        for (int i = 0; i < s.size(); i++)
        {
            if (dict.find(s.substr(0, i+1)) != dict.end())
            {
                dp[i] = true; continue;
            }
            for (int j = 0; j < i; j++)
                if (dp[j] && dict.find(s.substr(j+1, i-j)) != dict.end())
                {
                    dp[i] = true; break;
                }
        }
        vector<string> ans;
        if (dp[s.size()-1]) dfs(0, "", s, dict, ans); //存在才搜索
        return ans;
    }
    void dfs(int st, string cur, string s, unordered_set<string> &dict, vector<string> &ans)
    {
        if (st >= s.size())
        {
            ans.push_back(cur); return;
        }
        for (int i = st; i < s.size(); i++)
        {
            string word = s.substr(st, i-st+1);
            if (dict.find(word) != dict.end())
            {
                int len = cur.size();
                cur = len ? cur + " " + word : word;
                dfs(i+1, cur, s, dict, ans);
                cur = len ? cur.substr(0, len) : "";
            }
        }
    }
};