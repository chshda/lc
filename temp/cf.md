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

## [Jellyfish and Math](https://codeforces.com/contest/1875/problem/E)

给定初始点(a,b)和整数m，移动规则为 a=a&b 或 a=a|b 或 b=a^b 或 b=b^m，问走到(c,d)的最小步数。

移动规则为位运算，逐位考虑，对于第i位，(a, b, m) 的第i位，经过移动后要变成 (c, d) 的第i位。如果 (a, b, m) 的第i位和之前的某个第j位完全相同，则对应的 (c, d)的第j位也必须相同，因为他们运算的过程是一样的。

对 (a, b, m) 的每一位的情况，去重后最多有8种可能的情况。映射后的 (c, d) 最多有4种情况，额外考虑不存在的情况使用5个状态表示。可以使用一个 $map<int,int>$ 把8种情况的每一种情况 映射到 5个状态中的一个。map可以简化为一个长为8的数组表示，进一步当做一个长为8的5进制数表示这个状态。

有了状态怎么转移，使用刷表法，从小到大枚举状态，从不需要移动的状态出发（c/d和a/b一样），使用BFS，一次次移动，直到移不动为止。由于状态空间大小最多为 $5^8$，复杂度不会太高。

```cpp
using state = array<int, 8>;
static const int N = pow(5, 8);
vector<int> dp(N, -1);

state decode(int x) {
    state ans; for (int i = 0; i < 8; i++) ans[i] = 0;
    int id = 0;
    while (x) ans[id++] = x % 5, x /= 5;
    return ans;
}

int encode(state s) {
    int ans = 0;
    for (int i = 7; i >= 0; i--) ans = ans * 5 + s[i];
    return ans;
}

bool is_init_state(int x) {
    auto s = decode(x);
    for (int i = 0; i < 8; i++) if (s[i] != 4 && s[i] != (i >> 1)) return false;
    return true;
}

int perform(int x, int op) {
    state s = decode(x);
    for (int i = 0; i < 8; i++) {
        if (s[i] == 4) continue;
        int m = i&1, c = s[i]>>1&1, d = s[i]&1;
        if (op == 0) c &= d;
        else if (op == 1) c |= d;
        else if (op == 2) d ^= c;
        else d ^= m;
        s[i] = (c << 1) | d;
    }
    return encode(s);
}

void init() {
    for (int i = 0; i < N; i++) {
        if (dp[i] != -1 || !is_init_state(i)) continue;
        dp[i] = 0;
        queue<int> q; q.push(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int op = 0; op < 4; op++) {
                int y = perform(x, op);
                if (dp[y] == -1) {
                    dp[y] = dp[x] + 1; q.push(y);
                } 
            }
        }
    }
}

void solve(int tc) {
    init();
    int A, B, C, D, M; cin >> A >> B >> C >> D >> M;
    state s; for (int i = 0; i < 8; i++) s[i] = 4;
    for (int i = 0; i < 30; i++) {
        int a = A>>i&1, b = B>>i&1, c = C>>i&1, d = D>>i&1, m = M>>i&1;
        int id = (a << 2) | (b << 1) | m, val = (c << 1) | d;
        if (s[id] != 4 && s[id] != val) { cout << -1 << endl; return; }
        s[id] = val;
    }
    cout << dp[encode(s)] << endl;
}
```