// Source: https://oj.leetcode.com/problems/merge-intervals/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    struct cmp //区间排序仿函数
    {
        bool operator()(const Interval &a, const Interval &b)
        {
            return a.start < b.start || (a.start == b.start && a.end < b.end);
        }
    };

    vector<Interval> merge(vector<Interval> &intervals) {
        vector<Interval> ans;
        if (intervals.empty()) return ans;
        
        sort(intervals.begin(), intervals.end(), cmp()); //按起点排序
        int st = intervals[0].start, ed = intervals[0].end;
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i].start > ed) //新的区间
            {
                ans.push_back(Interval(st, ed));
                st = intervals[i].start, ed = intervals[i].end;
            }
            else if (intervals[i].end > ed) //可以合并
                ed = intervals[i].end;
        }
        ans.push_back(Interval(st, ed));
        return ans;
    }
};