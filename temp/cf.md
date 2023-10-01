# CF

## [Jellyfish and Game](https://codeforces.com/contest/1874/problem/A)

A有 $n$ 个数，B有 $m$ 个数，进行 $k$ 轮操作，每次可以选择自己的一个数和对方的一个数交换，也可以不换。求A的最大和。

贪心。考虑最大值：

* $max(a) > max(b)$：A一定会有最大值（大不了不换）
* $max(a) < max(b)$：$min(a) < max(b)$，A会交换得到最大值

最小值：

* $min(a) < min(b)$：A会交换把最小值给B（交换A肯定能得到更大的）
* $min(a) > min(b)$：A不可能把B的最小值换过来，B会有最小值

于是，第一轮操作后最大值一定在A里，最小值一定在B里。第二轮B肯定最最小值和A的最大值换，然后第三轮A又换回来，两轮两轮循环。

```cpp
void solve(int tc) {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

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
