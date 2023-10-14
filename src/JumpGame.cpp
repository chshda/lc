// Source: https://oj.leetcode.com/problems/jump-game/

class Solution {
public:
    bool canJump(int A[], int n) {
        int mx = A[0]; //当前能搞到达的最远距离
        for (int i = 1; i < n; i++)
        {
            if (mx == 0) return false;
            mx--; //走一步，最远距离减一
            mx = max(mx, A[i]);
        }
        return true;
    }
};