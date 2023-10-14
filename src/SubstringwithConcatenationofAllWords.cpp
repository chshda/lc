// Source: https://oj.leetcode.com/problems/substring-with-concatenation-of-all-words/

class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        int m = S.size(), n = L.size(), len = L[0].size();
        
        map<string, int> mp, cur;
        for (int i = 0; i < n; i++)
            mp[L[i]]++; //每个词出现的次数
        
        vector<int> ans;
        for (int i = 0, j, k; (k = i + n * len) <= m; i++) //枚举起点
        {
            cur.clear();
            for (j = i; j < k; j += len) //一个单词一个单词前进
            {
                string tem = S.substr(j, len);
                cur[tem]++;
                if (cur[tem] > mp[tem]) break;
            }
            if (j >= k) ans.push_back(i);
        }
        return ans;
    }
};