// Source: https://oj.leetcode.com/problems/roman-to-integer/

class Solution {
public:
    int r2i(char c)
    {
        if (c == 'I') return 1;
        if (c == 'V') return 5;
        if (c == 'X') return 10;
        if (c == 'L') return 50;
        if (c == 'C') return 100;
        if (c == 'D') return 500;
        if (c == 'M') return 1000;
    }
    
    int romanToInt(string s) {
        if (s.length() == 0) return 0;
        
        int ans = r2i(s[0]);
        for (int i = 1; i < s.length(); i++)
        {
            int prev = r2i(s[i-1]), cur = r2i(s[i]);
            if (prev < cur) //小数接大数
                ans = ans - prev + cur - prev;
            else
                ans = cur + ans;
        }
        return ans;
    }
};
