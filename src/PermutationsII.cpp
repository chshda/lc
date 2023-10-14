// Source: https://oj.leetcode.com/problems/permutations-ii/

class Solution {
public:
    bool exist(const vector<int> &cur, int st, int ed) //判断ed位置的数字在[st, ed)是否出现
    {
        for (int i = st; i < ed; i++)
            if (cur[i] == cur[ed]) 
                return true;
        return false;
    }
    void f(int x, vector<int> &cur, vector<vector<int>> &ans)
    { //当前位置，当前选择的排列，答案
        if (x == cur.size()) //到达末尾
        {
            ans.push_back(cur);
            return;
        }
        for (int i = x; i < cur.size(); i++) //选择x及其后面的数字
            if (!exist(cur, x, i)) //没出现才能选择
            {
                swap(cur[x], cur[i]);
                f(x+1, cur, ans);
                swap(cur[x], cur[i]); //回溯
            }
    }
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int>> ans;
        f(0, num, ans);
        return ans;
    }
};