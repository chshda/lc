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
