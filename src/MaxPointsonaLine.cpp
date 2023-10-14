// Source: https://oj.leetcode.com/problems/max-points-on-a-line/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point> &points) {
        int n = points.size();
        if (n < 3) return n;
        
        int ans = 0;
        for (int i = 0; i < n; i++) //枚举每个点
        {
            int same = 1;
            map<double, int> mp; //统计斜率
            for (int j = 0; j < n; j++)
            {
                if (j == i) continue;
                int x0 = points[i].x, y0 = points[i].y, x1 = points[j].x, y1 = points[j].y;
                if (x0 == x1 && y0 == y1) 
                {
                    same++; continue;
                }
                if (x0 == x1)
                    mp[INT_MAX]++;
                else
                    mp[double(y1-y0)/(x1-x0)]++;
            }
            ans = max(ans, same);
            for (map<double, int>::iterator p = mp.begin(); p != mp.end(); ++p)
                ans = max(ans, p->second + same);
        }
        return ans;
    }
};