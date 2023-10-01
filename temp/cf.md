# CF

## [Jellyfish and Game](https://codeforces.com/contest/1874/problem/A)

A有 $n$ 个数，B有 $m$ 个数，轮流进行 $k$ 次操作，每次可以选择自己的一个数和对方的一个数交换，也可以不换。求A的最大和。

贪心。考虑最大值，如果在A手上，A肯定不会换给B，如果在B手上，A肯定会换过来。最小值同理，如果在A手上，A肯定会换给B，如果在B手上，A肯定不会换过来。所以第一轮操作后最大值一定在A里，最小值一定在B里。第二轮B肯定拿最小值和A的最大值换，然后第三轮A又换回来，两轮两轮循环。

```cpp
void solve(int tc) {
    int n, m, k; vector<int> a(n), b(m);

    int mna = 0, mxb = 0;
    for (int i = 1; i < n; i++) if (a[i] < a[mna]) mna = i;
    for (int i = 1; i < m; i++) if (b[i] > b[mxb]) mxb = i;
    if (a[mna] < b[mxb]) swap(a[mna], b[mxb]);

    if (--k & 1) {
        int mxa = 0, mnb = 0;
        for (int i = 1; i < n; i++) if (a[i] > a[mxa]) mxa = i;
        for (int i = 1; i < m; i++) if (b[i] < b[mnb]) mnb = i;
        if (b[mnb] < a[mxa]) swap(b[mnb], a[mxa]);
    }

    cout << accumulate(a.begin(), a.end(), 0LL) << endl;
}
```

## [Jellyfish and Green Apple](https://codeforces.com/contest/1875/problem/C)

n个1kg的苹果m个人平均分，每切一刀可以把一块苹果平均分成两份，最少切几刀可以完成分配。

当 $n>=m$ 时可以不断每人分一个苹果直到 $n < m$，然后每人拿到 $n/m$ 重的苹果。因为切割后的苹果重量只能是 $1/2^i$，约分后的m必须是2的整数幂，否则无解。

约分后的 $n/m$，把 n 拆开2进制表示，写成多个分子为1的分数的和，每个分数表示一小块苹果，于是1的数量则为每个人拿到的苹果的块数，乘以m为总块数，减去n为切的次数。

```cpp
void solve(int tc) {
    int n, m; cin >> n >> m;
    n %= m;
    int a = n / gcd(n, m), b = m / gcd(n, m);
    if (__builtin_popcount(b) > 1) cout << -1 << endl;
    else cout << 1LL * m * __builtin_popcount(a) - n << endl;
}
```

## [Jellyfish and Mex](https://codeforces.com/contest/1875/problem/D)

n个数，执行n次操作，每次选一个数删掉，把剩下的数组的mex加进和里，求最小和。

贪心DP。选小于mex的一个数，删到没有为止，再在剩下的数组里重复进行，DP。

* dp[i]: [0,i]里取到的最小和
* dp[i] = min(dp[j-1] + (cnt[j]-1) * (i+1) + j) (枚举j，j-1特判)

```cpp
void solve(int tc) {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0, t; i < n; i++) if (cin >> t, t < n) a[t]++;
 
    int mex = 0;
    while (mex < n && a[mex]) mex++;
    if (mex == 0) { cout << 0 << endl; return; }
 
    vector<int> dp(n, INT_MAX);
    for (int i = 0; i < mex; i++) {
        for (int j = 0; j <= i; j++) dp[i] = min(dp[i], (j-1<0 ? 0 : dp[j-1]) + (a[j]-1) * (i+1) + j);
    }
    cout << dp[mex-1] << endl;
}
```