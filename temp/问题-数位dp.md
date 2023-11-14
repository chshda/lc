# 数位dp

## [最大为n的数字组合](https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/description/)

给定若干个数字，每个可以使用任意次，求组合出来的数字<=n的总个数。

```cpp
int atMostNGivenDigitSet(vector<string>& digits, int n) {
    auto s = to_string(n);
    int m = s.size();
    int dp[m]; memset(dp, -1, sizeof(dp));
    function<int(int, bool, bool)> f = [&](int i, bool limit, bool started) -> int{
        if (i == m) return started;
        if (!limit && started && dp[i] != -1) return dp[i];

        int ans = 0;
        if (!started) ans += f(i+1, false, false);
        for (int d = 1, up = limit ? s[i]-'0' : 9; d <= up; d++) {
            if (ranges::find(digits, to_string(d)) == digits.end()) continue;
            ans += f(i+1, limit && d == up, true);
        }
        if (!limit && started) dp[i] = ans;
        return ans;
    };
    return f(0, true, false);
}
```