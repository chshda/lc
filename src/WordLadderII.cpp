// Source: https://oj.leetcode.com/problems/word-ladder-ii/

class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict)
    {
        map<string, vector<string> > mp; //生成表示路径的树
    
        unordered_set<string> l[3], *pre = l, *cur = l+1, *nxt = l+2, *tp; //保存BFS遍历的节点顺序
        cur->insert(start);
        
        while (1) //深度优先搜索
        {
            nxt->clear();
            for (auto p = cur->begin(); p != cur->end(); p++)
            {
                string w = *p;
                for (int i = 0; i < w.size(); i++)
                    for (char j = 'a'; j <= 'z'; j++)
                    {
                        string tem = w; tem[i] = j;
                        if (dict.count(tem)>0 && pre->count(tem)==0 && cur->count(tem)==0)
                        {
                            mp[w].push_back(tem);
                            nxt->insert(tem);
                        }
                    }
            }
            if (nxt->count(end) > 0) break;
    		if (nxt->empty()) { mp.clear(); break; }
            tp = pre, pre = cur, cur = nxt, nxt = tp;
        }
            
        vector<vector<string> > ans;
        vector<string> curv(1, start);
        dfs(start, end, mp, curv, ans); //生成答案
        return ans;
    }

    void dfs(string s, string end, map<string, vector<string> > &mp, vector<string> &cur, vector<vector<string> > &ans)
    {
        if (s == end)
        {
            ans.push_back(cur); return;
        }
        for (int i = 0; i < mp[s].size(); i++)
        {
            cur.push_back(mp[s][i]);
            dfs(mp[s][i], end, mp, cur, ans);
            cur.pop_back();
        }
    }
};