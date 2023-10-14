// Source: https://oj.leetcode.com/problems/permutations/

class Solution {
public:
    void f(int x, vector<int> &cur, vector<vector<int> > &ans){
        if (x == cur.size()) //到达末尾
        {
            ans.push_back(cur);
            return;
        }
        for (int i = x; i < cur.size(); i++) //从第x个数及其后面选择一个
        {
            swap(cur[x], cur[i]);
            f(x+1, cur, ans);
            swap(cur[x], cur[i]);
        }
    }
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > ans;
        f(0, num, ans);
        return ans;
    }
};