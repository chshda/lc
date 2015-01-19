// Source: https://oj.leetcode.com/problems/longest-substring-without-repeating-characters/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0, cur = 0;
        unordered_map<char, int> mp;
        for (int i = 0, st = 0; i < s.size(); i++)
        {
            if(m.find(s[i]) == m.end()) //尚未出现
                cur++, m[s[i]] = i;
            else
            {
                if (m[s[i]] < st)       //出现在st前
                    cur++, m[s[i]] = i;
                else                    //出现在st后
                    st = m[s[i]] + 1, cur = i - st + 1, m[s[i]] = i;
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};