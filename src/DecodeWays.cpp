// Source: https://oj.leetcode.com/problems/decode-ways/

class Solution {
public:
    int numDecodings(string s) { //DP
        if (s.empty() || s[0] == '0') return 0;
        
        int dp[10005]; //前i个字符解码方式数
        dp[0] = dp[1] = 1;
        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == '0')
            {
                if (s[i-1] != '1' && s[i-1] != '2') return 0;
                dp[i+1] = dp[i-1];
            }
            else
            {
                dp[i+1] = dp[i];
                int t = (s[i-1]-'0') * 10 + s[i]-'0';
                if (t >= 10 && t <= 26) dp[i+1] += dp[i-1];
            }
        }
        return dp[s.size()];
    }
};