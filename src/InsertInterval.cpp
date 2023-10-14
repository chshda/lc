// Source: https://oj.leetcode.com/problems/insert-interval/

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
    bool overlaps(const Interval &a, const Interval &b) //判断区间是否重叠
    {
        return (a.start >= b.start && a.start <= b.end) || (b.start >= a.start && b.start <= a.end);
    }
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> ans;
        for (int i = 0, inserted = 0; i < intervals.size();)
        {
            if (inserted) //已经插入
            {
                ans.push_back(intervals[i++]);
                continue;
            }
            
            if (newInterval.end < intervals[i].start) //可以插入而不必合并
            {
                ans.push_back(newInterval);
                inserted = 1;
            }
            
            if (!overlaps(intervals[i], newInterval)) //不能插入
                ans.push_back(intervals[i++]);
            else //可以插入，但需要合并
            {
                while (i < intervals.size() && overlaps(intervals[i], newInterval)) //不断合并
                {
                    newInterval.start = min(newInterval.start, intervals[i].start);
                    newInterval.end = max(newInterval.end, intervals[i].end);
                    i++;
                }
                ans.push_back(newInterval);
                inserted = 1;
            }
        }
        if (ans.empty() || newInterval.start > ans.back().end) //最后一个元素
            ans.push_back(newInterval);
        return ans;
    }
};