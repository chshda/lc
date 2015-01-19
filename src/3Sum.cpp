// Source: https://oj.leetcode.com/problems/3sum/

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > ans;
        sort(num.begin(), num.end());
        
        for (int i = 0, n = num.size(); i < n-2; i++) //枚举第一个数
        {
            if (i > 0 && num[i] == num[i-1]) continue; //第一个数去重
            
            for (int j = i+1, k = n-1; j < k;) //两边往中间扫描,寻找后两个数
            {
                int s = num[i] + num[j] + num[k];
                if (s == 0)
                {
                    int tema[3] = {num[i], num[j], num[k]};
                    vector<int> temv(tema, tema + 3);
                    ans.push_back(temv);
                    
                    while (j+1 < n && num[j] == num[j+1]) j++; //第二个数去重
                    while (k-1 >= 0 && num[k] == num[k-1]) k--;//第三个数去重
                    j++, k--;
                }
                else if(s > 0)
                {
                    while (k-1 >= 0 && num[k] == num[k-1]) k--;//第二个数去重
                    k--;
                }
                else
                {
                    while (j+1 < n && num[j] == num[j+1]) j++;//第三个数去重
                    j++;
                }
            }
        }
        return ans;
    }
};