// Source: https://oj.leetcode.com/problems/valid-palindrome/

class Solution {
public:
    bool isPalindrome(string s) {
        string news;
        for (int i = 0; i < s.length(); i++)
            if (isalpha(s[i]) || isdigit(s[i])) //只考虑字母和数字
                news.push_back(tolower(s[i]));
        
        for (int i = 0, j = news.length()-1; i < j; i++, j--)
            if(news[i] != news[j])
                return false;
        
        return true;
    }
};