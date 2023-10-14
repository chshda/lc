// Source: https://oj.leetcode.com/problems/3sum-closest/

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        int ans = -1, diff = 1 << 30; //答案，最小距离
        for (int i = 0; i < num.size() - 2; i++) //枚举第一个数字
        {
            int j = i + 1, k = num.size() - 1;
            while (j < k) //首尾向中间扫描，寻找后两个数字
            {
                int t = num[i] + num[j] + num[k], tdiff;
                if (t > target) k--, tdiff = t - target; //大于target，减小
                else j++, tdiff = target - t;            //小于target，增加
                if (tdiff < diff) diff = tdiff, ans = t; //更新
            }
        }
        return ans;
    }
};