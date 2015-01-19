// Source: https://oj.leetcode.com/problems/maximum-gap/

class Solution {
public:
    int maximumGap(vector<int> &num) {
        int n = num.size();
        if (n < 2) return 0;
        
        int mx = *max_element(num.begin(), num.end());
        int mn = *min_element(num.begin(), num.end());
            
        double w = (mx - mn) / (n - 1.0); //宽度
        vector<vector<int>> v(n - 1);     //n-1个桶
        for (auto p = num.begin(); p != num.end(); p++)
            if (*p != mn && *p != mx)
                v[(*p - mn) / w].push_back(*p);
        
        int pre = mn, ans = INT_MIN;
        for (auto p1 = v.begin(); p1 != v.end(); p1++)
            if (!(*p1).empty())
            {
                int t1 = *min_element((*p1).begin(), (*p1).end());
                int t2 = *max_element((*p1).begin(), (*p1).end());
                ans = max(ans, t1 - pre), pre = t2;
            }
        return max(ans, mx - pre);
    }
};