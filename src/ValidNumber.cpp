// Source: https://oj.leetcode.com/problems/valid-number/

class Solution {
public:
    bool isNumber(const char *s) {
        if (!s) return false;
		
        while (isspace(*s)) s++;         //前导空格
        if (*s == '+' || *s == '-') s++; //正负号
        if (!*s) return false;
        
        bool hase = false, hasdot = false;
        const char *olds = s;
        for (; *s; s++)
        {
            if (isdigit(*s)) continue;
            else if (*s == '.')
            {
                if (hase || hasdot) return false; //同时有.和e
                if (s == olds && !isdigit(*(s+1))) return false; //至少有一个小数部位
                hasdot = true;
            }
            else if (*s == 'e')
            {
                if (hase || s == olds) return false; //同时又.和e
                s++;
                if (*s == '+' || *s == '-') s++;//正负号
                if (!isdigit(*s)) return false; //至少一个数字表示次方
                hase = true;
            }
            else if (isspace(*s))
            {
                while (*s) if (!isspace(*s++)) return false; //后续全为空格
                return true;
            }
            else //非法字符
                return false;
        }
        return true;
    }
};