// Source: https://oj.leetcode.com/problems/combinations/

class Solution {
public:
    void f(int n, int k, vector<int> &v, vector<vector<int> > &ans)
    { //当前可以选择的最大数，剩余元素个数，当前选择，答案
        if (k == 0) //选完了
        {
            vector<int> tem = v;
            sort(tem.begin(), tem.end());
            ans.push_back(tem);
            return;
        }
        for (int i = n; i > 0; i--) //选择一个
        {
            v.push_back(i);
            f(i-1, k-1, v, ans);
            v.pop_back(); //回溯
        }
    }
    
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > ans;
        vector<int> v;
        f(n, k, v, ans);
        return ans;
    }
};