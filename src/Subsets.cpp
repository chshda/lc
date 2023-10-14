// Source: https://oj.leetcode.com/problems/subsets/

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > ans;
        vector<int> cur;
        sort(S.begin(), S.end());
        subsets(0, cur, S, ans);
        return ans;
    }
    void subsets(int id, vector<int> &cur, vector<int> &S, vector<vector<int> > &ans)
    { //当前可以选择的最小数，当前已选择的数字，给定的数组，答案
        ans.push_back(cur); //得到一个子集
        for (int i = id; i < S.size(); i++) 
        {
            cur.push_back(S[i]); //选择下一个数字
            subsets(i+1, cur, S, ans);
            cur.pop_back(); //回溯
        }
    }
    
    vector<vector<int> > subsets2(vector<int> &S) {
        vector<vector<int> > ans;
        vector<int> cur;
        sort(S.begin(), S.end());
        subsets2(0, cur, S, ans);
        return ans;
    }
    void subsets2(int x, vector<int> &cur, vector<int> &S, vector<vector<int> > &ans)
    {
        if (x == S.size())
        {
            ans.push_back(cur);
            return;
        }
        subsets2(x+1, cur, S, ans);
        cur.push_back(S[x]);
        subsets2(x+1, cur, S, ans);
        cur.pop_back();
    }
};