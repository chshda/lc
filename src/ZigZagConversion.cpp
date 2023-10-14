// Source: https://oj.leetcode.com/problems/zigzag-conversion/

class Solution {
public:
    string convert(string s, int nRows) {
        if (nRows == 1) return s;
        
        vector<string> v(nRows);
        for (int i = 0, r = 0, d = 1; i < s.length(); i++)
        {
            v[r] += s[i];
            if (r == 0) d = 1;         //向下
            if (r == nRows - 1) d = -1;//向上
            r += d;
        }
        string ans;
        for (int i = 0; i < nRows; i++) ans += v[i];
        return ans;
    }
};