// Source: https://oj.leetcode.com/problems/subsets-ii/

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > ans;
        vector<int> cur;
        sort(S.begin(), S.end());
        subsetsWithDup(0, cur, S, ans);
        return ans;
    }
    void subsetsWithDup(int x, vector<int> &cur, vector<int> &S, vector<vector<int> > &ans)
    {
        if (x == S.size())
        {
            ans.push_back(cur); return;
        }
        
        int cnt = 1, ed = x+1; //出现的个数，下一个数的位置
        while (ed < S.size() && S[ed] == S[x]) ed++, cnt++;
        
        subsetsWithDup(ed, cur, S, ans);
        for (int i = 0; i < cnt; i++)
        {
            cur.push_back(S[x]);
            subsetsWithDup(ed, cur, S, ans);
        }
        for (int i = 0; i < cnt; i++)
            cur.pop_back();
    }
};