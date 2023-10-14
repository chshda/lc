// Source: https://oj.leetcode.com/problems/word-ladder/

class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        if (start == end) return 1;
        
        map<string, int> mp;
        queue<string> q;
        
        q.push(start);
        mp[start] = 1;
        
        while (!q.empty())
        {
            string fr = q.front(); q.pop();
            
            for (int i = 0; i < fr.size(); i++)
                for (char j = 'a'; j <= 'z'; j++)
                {
                    string tem = fr; tem[i] = j;      
                    if (dict.find(tem)!=dict.end() && mp.find(tem)==mp.end())
                    {
                        if (tem == end) return mp[fr] + 1;
                        else
                        {
                            q.push(tem); mp[tem] = mp[fr] + 1;
                        }
                    }
                }
        }
        return 0;
    }
};