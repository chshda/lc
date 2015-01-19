// Source: https://oj.leetcode.com/problems/reverse-words-in-a-string/

class Solution {
public:
    string reverse(string s)
    {
        for (int i = 0, j = s.size()-1; i < j; i++, j--)
            swap(s[i], s[j]);
        return s;
    }
    void reverseWords(string &s)
    {
        string t = reverse(s); //翻转整个句子
        s.clear();
        for (int i = 0, j = 0; j < t.size(); j++)
        {
            if (t[j] == ' ') //翻转每个单词
            {
                if (i != j)
                {
                    string w = reverse(t.substr(i, j-i));
                    s = s.empty() ? w : s + " " + w;
                    i = j + 1;
                }
                while (j+1 < t.size() && t[j+1] == ' ') j++;
                i = j + 1;
            }
            else if (j == t.size() - 1)
            {
                string w = reverse(t.substr(i, j-i+1));
                s = s.empty() ? w : s + " " + w;
            }
        }
    }
};