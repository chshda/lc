// Source: https://oj.leetcode.com/problems/regular-expression-matching/

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        if (!s || !p) return false;
        
        if (!*p) return *s == '\0';
        
        if (*(p+1) == '*') //后一个为*，需要组合使用
        {
            while (true) //*可以匹配0个或多个
            {
                if (isMatch(s, p+2)) return true;
                if (*s == *p || (*p == '.' && *s != '\0')) s++;
                else break;
            }
        }
        else if(*s == *p || (*p == '.' && *s != '\0'))
            return isMatch(s+1, p+1);
        
        return false;
    }
};