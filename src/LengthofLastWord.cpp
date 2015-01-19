// Source: https://oj.leetcode.com/problems/length-of-last-word/

class Solution {
public:
    int lengthOfLastWord(const char *s) {
        if (!s || !*s) return 0;
        
        const char *ed = s; //最后一个单词的末尾
        while (*ed) ed++;
        ed--;
        while (ed != s && isspace(*ed)) ed--;
        
        const char *st = ed;//最后一个单词的开头
        while (st != s && !isspace(*st)) st--;
        
        return *st == ' ' ? ed - st : ed - st + 1;
    }
};