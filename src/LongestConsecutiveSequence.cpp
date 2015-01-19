// Source: https://oj.leetcode.com/problems/longest-consecutive-sequence/

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        set<int> s;
        for (auto p = num.begin(); p != num.end(); p++) //插入时间nlogn!
            s.insert(*p);
        
        int ans = 1, pre, first = 1, cnt = 0;
        for (auto p = s.begin(); p != s.end(); p++)
        {
            if (first) first = 0, cnt = 1;
            else
            {
                if (*p == pre + 1) cnt++;
                else cnt = 1;
            }
            pre = *p, ans = max(ans, cnt);
        }
        return ans;
    }
};