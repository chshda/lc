// Source: https://oj.leetcode.com/problems/combination-sum/

class Solution {
public:
    void dfs(int x, int sum, vector<int> &cur, vector<int> &candidates, vector<vector<int>> &ans, int target)
    { //当前位置，当前和，当前每个数字已选择的次数，候选数字，答案，目标
        if (sum == target)
        {
            vector<int> tem;
            for (int i = 0; i < x; i++)
                for (int j = 0; j < cur[i]; j++)
                    tem.push_back(candidates[i]);
            ans.push_back(tem);
            return;
        }
        if (x == candidates.size()) return;
        
        int k = (target - sum) / candidates[x]; //最多选择次数
        for (int i = 0; i <= k; i++)
        {
            cur[x] = i;
            dfs(x+1, sum + candidates[x] * i, cur, candidates, ans, target);
        }
    }
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> cur(candidates.size(), 0);
        vector<vector<int>> ans;
        dfs(0, 0, cur, candidates, ans, target);
        return ans;
    }
};