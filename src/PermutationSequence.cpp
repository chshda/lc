// Source: https://oj.leetcode.com/problems/permutation-sequence/

class Solution {
public:
    string getPermutation(int n, int k) { //康托展开
        int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
        
        k--;
        bool vs[10] = {0};
        string ans;
        for (int i = n-1; i >= 0; i--)
        {
            int t = k / fac[i]; k %= fac[i];
            int j, cnt = -1;
            for (j = 1; j <= n; j++)
            {
                if (!vs[j]) cnt++;
                if (cnt == t) break;
            }
            
            vs[j] = 1;
            ans += char(j + '0');
        }
        return ans;
    }
};