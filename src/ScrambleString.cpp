// Source: https://oj.leetcode.com/problems/scramble-string/

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        
        int a[26] = {0};
        for (int i = 0; i < s1.size(); i++)
            a[s1[i]-'a']++, a[s2[i]-'a']--;
        for (int i = 0; i < 26; i++)
            if (a[i]) return false;
        
        for (int i = 1; i < s1.size(); i++)
        {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) 
                return true;
            if (isScramble(s1.substr(0, i), s2.substr(s2.size()-i, i)) && isScramble(s1.substr(i), s2.substr(0, s2.size()-i)))
                return true;
        }
        
        return false;
    }
};