// Source: https://oj.leetcode.com/problems/combination-sum-ii/

class Solution {
public:
    void dfs(int id, int sum, vector<int> &vs, vector<int> &num, int target, vector<vector<int>> &ans)
    { //当前位置，当前和，该数字是否使用，候选数字，目标，答案
        if (sum >= target)
        {
            if (sum == target) //找到一个答案
            {
                vector<int> tem;
                for (int i = 0; i < num.size(); i++)
                    if (vs[i]) tem.push_back(num[i]);
                ans.push_back(tem);
            }
            return;
        }
        if (id == num.size()) return; //没得选了
        
        int j = id + 1; //下一个不相同的元素的位置
        while (j < num.size() && num[j] == num[id]) ++j;
        
        dfs(j, sum, vs, num, target, ans); //不选该数字
        
        for (int i = id; i < j; i++) //处理重复出现的数字
        {
           vs[i] = 1, sum += num[i];
           dfs(j, sum, vs, num, target, ans);
        }
        for (int i = id; i < j; i++) //回溯
            vs[i] = 0, sum -= num[i];
    }
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        vector<int> vs(num.size(), 0);
        vector<vector<int> > ans;    
        dfs(0, 0, vs, num, target, ans);
        return ans;
    }
};