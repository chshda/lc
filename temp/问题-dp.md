# 动态规划 DP

## [DI 序列的有效排列](https://leetcode.cn/problems/valid-permutations-for-di-sequence/description/)

长为n的DI序列，D为decreasing，I为increasing，问0-n的排列里有多少个满足这个pattern。

[题解](https://leetcode.com/problems/valid-permutations-for-di-sequence/solutions/168278/C++JavaPython-DP-Solution-O(N2)/)。动态规划，dp[i][j]表示第i个位置填的字符在剩下所有字符里排第j的总个数。第i个数及其后面一共有n-i个数，j的范围即为[0, n-i)，根据其是升序还是降序从i-1进行转移。

```cpp
int numPermsDISequence(string s) {
    int n = s.size();
    int dp[n+1][n+1]; memset(dp, -1, sizeof(dp));
    for (int i = 0; i <= n; i++) dp[0][i] = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'I') {
            for (int j = 0, tot = 0; j < n-i; j++) {
                dp[i+1][j] = tot = (tot + dp[i][j]) % mod;                    
            }
        } else {
            for (int j = n-i-1, tot = 0; j >= 0; j--) {
                dp[i+1][j] = tot = (tot + dp[i][j+1]) % mod;                    
            }
        }
    }
    return dp[n][0];
}
```