// Source: https://oj.leetcode.com/problems/4sum/

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target)
    {
        vector<vector<int> > ans;
        if (num.size() < 4) return ans;
        
        sort(num.begin(), num.end());
        for (int i = 0; i < num.size() - 3; i++) //枚举第一个数
        {
            if (i > 0 && num[i] == num[i-1]) continue; //避免重复
            vector<vector<int> > tem = threeSum(vector<int>(num.begin()+i+1, num.end()), target-num[i]); //解决3Sum
            for (int j = 0; j < tem.size(); j++)
            {
                tem[j].insert(tem[j].begin(), num[i]);
                ans.push_back(tem[j]);
            }
        }
        return ans;
    }
    vector<vector<int> > threeSum(vector<int> num, int target)
    {
        vector<vector<int> > ans;
        int n = num.size();
        for (int i = 0; i < n - 2; i++) //枚举第一个数字
        {
            if (i > 0 && num[i] == num[i-1]) continue; //避免重复
            for (int j = i+1, k = n-1; j < k;) //从两边向中间扫描
            {
                int s = num[i] + num[j] + num[k];
                if (s < target)
                {
                    while (j+1 < n && num[j] == num[j+1]) j++;
                    j++;
                }
                else if(s > target)
                {
                    while (k-1 >= 0 && num[k] == num[k-1]) k--;
                    k--;
                }
                else
                {
                    int tema[3] = {num[i], num[j], num[k]};
                    vector<int> temv(tema, tema + 3);
                    ans.push_back(temv);
                    while (j+1 < n && num[j] == num[j+1]) j++;
                    while (k-1 >= 0 && num[k] == num[k-1]) k--;
                    j++, k--;
                }
            }
        }
        return ans;
    }
};