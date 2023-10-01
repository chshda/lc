# 二分查找

## STL

标准库提供了 $>=x$ (lower_bound) 和 $>x$ (upper_bound) 两种情况的API，如果要 $<= x$ 或者 $< x$ 的情况可以进行转化。

* 求 $<= x$ 的最大数，可以用upper_bound求出 $> x$ 的最小数，再减一即为 $<= x$ 最大数
* $>= x$ 和 $> x$ 也可以互相转化，$> x$ 等价于 $>= (x+1)$

如果查找一个很大的数，返回last下标，相反地，如果查找一个很小的数，返回first下标（因为first满足查找要求）

```cpp
// lower_bound：>=x 的第一个数字
lower_bound(a.begin(), a.end(), x);

// upper_bound：>x 的第一个数字
upper_bound(a.begin(), a.end(), x);

// 自定义比较函数
lower_bound(a.begin(), a.end(), x, [&](auto &a, int v) { return a[0] < v; });
```

## 手写

左闭右闭区间写法。[st, ed]满足ok条件的第一个位置：`0 ... 0 1 1 ... 1`（第一个1）

```cpp
int binary_search() {
    auto ok = [&](int x) { return true/false; };
    int st = 0, ed = INT_MAX;
    while (st < ed) {
        int m = st + ed >> 1; // 加号优先级大于右移
        if (ok(m)) ed = m;
        else st = m + 1;
    }
    return st;
}
```

[st, ed]满足ok条件的最后位置：`1 ... 1 0 0 ... 0`（最后一个1）

```cpp
int binary_search() {
    auto ok = [&](int x) { return true/false; };
    int st = 0, ed = INT_MAX;
    while (st < ed) {
        int m = st + ed + 1 >> 1; // 因为下面有st=m，当两个数相邻时中间值要取右边那个，避免死循环
        if (ok(m)) st = m;
        else ed = m - 1;
    }
    return st;
}
```