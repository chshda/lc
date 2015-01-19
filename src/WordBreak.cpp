// Source: https://oj.leetcode.com/problems/word-break/

class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
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
        return dp[s.size()-1];
    }
};