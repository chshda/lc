// Source: https://oj.leetcode.com/problems/minimum-window-substring/

class Solution {
public:
    string minWindow(string S, string T) {
        if (S.empty() || T.empty()) return "";
        
        int l1 = S.size(), l2 = T.size(), cnt1[256] = {0}, cnt2[256] = {0};
        for (int i = 0; i < l2; i++) cnt2[T[i]]++; //记录T每个字符出现的次数
        
        int st, ed, len = INT_MAX, cnt = 0;
        for (int i = 0, j = 0; j < l1; j++) //双指针同时扫描，i为起点，j为终点
        {
            if (++cnt1[S[j]] <= cnt2[S[j]]) cnt++; 
            if (cnt == l2) //包含全部
            {
                while (cnt1[S[i]] > cnt2[S[i]]) cnt1[S[i++]]--;
                if (j-i+1 < len) len = j-i+1, st = i, ed = j;
            }
        }
        return len == INT_MAX ? "" : S.substr(st, ed - st + 1);
    }
};