// Source: https://oj.leetcode.com/problems/jump-game-ii/

class Solution {
public:
    int jump(int A[], int n) {
        int cnt = 0, mx = 0, cur = 0; //最小步数，最远位置，当前位置
        for (int i = 0; i < n; ++i)
        {
            if (cur < i) cnt++, cur = mx; //当前位置没到i，需要走多一步
            mx = max(mx, i + A[i]); //更新最远位置
        }
        return cnt;
    }
};