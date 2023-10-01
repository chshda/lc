> 个人编程笔记


# 代码

**API**

```cpp
vector<int> a;

sort(a.begin(), a.end());
sort(a.begin(), a.end(), greater<int>());
sort(a.begin(), a.end(), [](auto &a, auto &b) { return a < b; });

*max_element(a.begin(), a.end()); // min_element same
*max_element(a.begin(), a.end(), [](auto &a, auto &b) { return a < b; });

accumulate(a.begin(), a.end(), 0);
accumulate(a.begin(), a.end(), 1, [](int tot, int cur) { return tot * cur; });

a.erase(0, a.find_first_not_of('0')); // 去除前导0
iota(a.begin(), a.end(), 5); // 从5开始递增给a赋值

// 前缀和 prefix sum，保存在s里，s的长度比a大1
int s[n]; s[0] = 0; partial_sum(a.begin(), a.end(), s + 1);
// 区间和 - 左闭右开区间，sum [a, c) = s[c] - s[a] - 这个方便
// 区间和 - 左闭右闭区间，sum [a, b] = sum [a, b+1) = s[b+1] - s[a]

unordered_set<int> s(a.begin(), a.end());
for (auto &[k, v] : mp) {}

function<int(int, int)> gcd = [&](auto &a, auto &b) { return b == 0 ? a : gcd(b, a % b); };

unique(a.begin(), a.end()) // 去除相邻重复元素，连续的重复数字只会保留一个
a.resize(unique(a.begin(), a.end()) - a.begin()) // 去除相邻重复元素（若要完全去重需要先排序）

equals(a.begin()+1, a.end(), a.begin()) // 判断a全部元素相等, a[1]==a[0], a[2]==a[1] ...

// 下标排序
int id[n]; iota(id, id+n, 0);
sort(id, id+n, [&](int i, int j) { return a[i] < a[j]; });

// 枚举4个方向
static const int dd[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
for (auto [dx, dy] : dd) { cout << dx << " " << dy << endl; }

（x, y) -> x * n + y // m*n矩阵 点(x,y)映射成为一个数字

int(a+b-1) / b) // ceil, a/b向上取整

// 二分快速幂 quick pow, a ^ b % c 
ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % c;
        a = a * a % c, b >>= 1;
    }
    return ans;
}

ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c;
    return ans;
}
```

**data structure**
```cpp
deque<int> q;
q.front(); q.push_front(); q.emplace_front(); q.pop_front();
q.back(); q.push_back(); q.emplace_back(); q.pop_back();

// 优先队列 - 比较函数里优先值高的会尽量被保存在队里，优先值低的会被先pop掉
auto cmp = [&](pii &a, pii &b) { return a.second > b.second || (a.second == b.second && a < b); };
priority_queue<pii, vector<pii>, decltype(cmp)> q(cmp);

make_heap(a.begin(), a.end(), greater<int>()); // 最大的优先，保留在数组里，最小的会被先pop掉
pop_heap(a.begin(), a.end(), greater<int>()); a.pop();
a.push_back(1); push_heap(a.begin(), a.end(), greater<int>());
```

区间操作
```cpp
// 区间合并必须按左端点排序
vector<pii> merge(vector<pii> v) {
    sort(v.begin(), v.end());
    vector<pii> ans;
    ans.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        int &b = ans.back().second;
        if (v[i].first <= b) {
            b = max(b, v[i].second);
        } else {
            ans.push_back(v[i]);
        }
    }
    return ans;
}

// 区间查找不能使用upper_bound(pii(x, 0))
// 因为起点相同时，会认为该区间严格大于待查找区间([x, 0])，因为左端点相同时会比较右端点，而他的右端点大
pii find(vector<pii> &v, int x) {
    auto p = lower_bound(v.begin(), v.end(), pii(x+1, 0));
    if (p == v.begin()) return pii(-1, -1);
    if (x <= (--p)->second) return *p;
    return pii(-1, -1);
}
```

**二分查找 binary search**
标准库提供了 >=x (lower_bound) 和 >x (upper_bound) 两种情况的API，如果要 <= x 或者 <x 的情况可以进行转化。
 - 求 <= x的最大数，可以用upper_bound求出 >x 的最小数，再减一即为 <= x最大数
 -  `>= x` 和 `>x` 也可以互相转化，`>x` 等价于 `>=(x+1)`
 如果查找一个很大的数，返回last下标，相反地，如果查找一个很小的数，返回first下标（正常，因为first满足查找要求）
```cpp
// lower_bound：>=x 的第一个数字
lower_bound(a.begin(), a.end(), x);
// upper_bound：>x 的第一个数字
upper_bound(a.begin(), a.end(), x);

// [st, ed]满足ok条件的第一个位置：0 ... 0 1 1 ... 1（第一个1）
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

// [st, ed]满足ok条件的最后位置：1 ... 1 0 0 ... 0（最后一个1）
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

// 自定义比较函数
lower_bound(a.begin(), a.end(), x, [&](auto &a, int v) { return a[0] < v; });
```

 **离散化**

```cpp
vector<int> a; // 待离散化
vector<int> t = a;
sort(t.begin(), t.end());
t.erase(unique(t.begin(), t.end()), t.end());
for (auto &i : a) i = lower_bound(t.begin(), t.end(), i) - t.begin() + 1;
```

 **skleton**

```cpp
#include <bits/stdc++.h> 
using namespace std; 

typedef long long ll;
typedef pair<int, int> pii;

int init = []() { return 0; }();

void solve(int tc) {} 

int32_t main() {
#ifdef LOCAL_PROJECT
    freopen("data/in.txt", "r", stdin);
    freopen("data/out.txt", "w", stdout);
    freopen("data/error.txt", "w", stderr);
#endif 
    ios::sync_with_stdio(false); cin.tie(0); 
    int tc; cin >> tc; for (int i = 1; i <= tc; i++) solve(i); 
    return 0;
}
```

**并查集**
```cpp
struct DisjoinSet {
    vector<int> pa, size;
    DisjoinSet(int n): pa(n), size(n, 1) { for (int i = 0; i < n; i++) pa[i] = i; }
    int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        pa[y] = x; size[x] += size[y];
};
```




**单调栈**
求左边/右边 第一个 大于/大于等于/小于/小于等于 自己的数。
- 假如是右边第一个大于a[i]的数，从左往右遍历，对于当前的a[i]，他的答案在右边还没遍历到，只能在后面他出栈的时候更新他的答案，于是此时他弹出其他元素出栈，更新那些元素的答案。因为求右边第一个j满足 a[j] > a[i]，对于当前数字，如果他大于栈顶，则栈顶的答案位当前数字，并将其出栈。
- 假如是左边第一个大于等于a[i]的数，从左往右遍历，对于当前的a[i]，弹出栈里小于a[i]的数字，则剩下栈顶（如果非空）元素极为当前元素的答案。
总结，固定从左往右遍历，如果求右边第一个xxx的数字，则在出栈的时候更新出栈元素的答案（当前元素），如果求左边第一个xxx的数字，则在每个元素入栈的时候更新其答案（栈顶）
```cpp
// left[i]: i左边 >= a[i]的第一个数的下标
// right[i]: i右边 >a[i]的第一个数的下标
int n = a.size(), left[n], right[n];
fill(left, left+n, -1);
fill(right, right+n, n);
stack<int> st;
for (int i = 0; i < n; i++) {
    while (!st.empty() && w[a[st.top()]] < w[a[i]]) {
        right[st.top()] = i;
        st.pop();
    }
    if (!st.empty()) left[i] = st.top();
    st.push(i);
}
```

**最短路**
```cpp
void buildGraph() {
    vector<vector<pii>> g(n);
    for (auto &e : edges) {
        int u = e[0], v = e[1], d = e[2];
        g[u].emplace_back(v, d); g[v].emplace_back(u, d);
    }
}

// 堆优化 - 给定起点-终点
int dijkstra(const vector<vector<pii>> &g, int n, int start, int end) {
    vector<int> dis(n, INT_MAX); dis[start] = 0;
    priority_queue<pii, vector<pii>, greater<>> q; q.emplace(0, start);
    while(!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (x == end) return d;
        if (d > dis[x]) continue;
        for (auto [y, nd] : g[x]) {
            nd += d; if (nd < dis[y]) { dis[y] = nd; q.emplace(nd, y); }
        }
    }
    return -1;
}

// 堆优化 - 起点到所有其他顶点    
vector<int> dijkstra(const vector<vector<pii>> &g, int n, int start) {
    vector<int> dis(n, INT_MAX); dis[start] = 0;
    priority_queue<pii, vector<pii>, greater<>> q; q.emplace(0, start);
    while (!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (d > dis[x]) continue;
        for (auto [y, nd] : g[x]) {
            nd += d; if (nd < dis[y]) { dis[y] = nd; q.emplace(nd, y); }
        }
    }
    return dis;
}

// 朴素算法
int dijkstra(const vector<vector<pii>> &g, int n, int start, int end) {
    vector<int> dis(n, INT_MAX), vs(n, false);
    dis[start] = 0;
    while (true) {
        int mn = -1;
        for (int i = 0; i < n; i++) { if (!vs[i] && (mn == -1 || dis[i] < dis[mn])) mn = i; }
        if (mn == -1 || dis[mn] == INT_MAX) return -1;
        if (mn == end) return dis[mn];
        vs[mn] = true;
        for (auto [y, w] : g[mn]) { if (dis[mn] + w < dis[y]) dis[y] = dis[mn] + w; }
    }
    return -1;
}   
```

**分解质因数**
```cpp
vector<int> primeFactorization(int num) {
    vector<int> ans;
    int up = (int)sqrt(num) + 1;
    for (int i = 2; i < up; ++i) { while (num % i == 0) { num /= i; .push_back(i); } }
    if (num != 1) { ans.push_back(num); }
    return ans;
}

// 筛法筛素数, w[i]表示质因数个数（w[i] == 1表示i为素数）
static const int mx = 1e5 + 1;
int w[mx];
int init = [](){
    for (int i = 2; i < mx; i++) {
        if (w[i] == 0) { // prime number
            for (int j = i; j < mx; j += i) w[j]++;
        }
    }
    return 0;
}();
```

**组合数**
```cpp
int c[mxm+1][mxn+1]; // combination, C(n, k) = c[n][k]
int init = [](){
    c[0][0] = 1;
    for (int i = 1; i <= mxm; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= mxn; j++) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    return 0;
}();

long long comb(long long m, long long n) {
    long long ans = 1;
    for (long long x = m - n + 1, y = 1; y <= n; x++, y++) ans = ans * x / y;
    return ans;
}

// python combination
comb(m, n)
```

**最长上升子序列**
```cpp
int lengthOfLIS(vector<int>& a) {
    vector<int> vt;
    for (auto i : a) {
        if (vt.empty() || i > vt.back()) vt.push_back(i);
        else *lower_bound(vt.begin(), vt.end(), i) = i;
    }
    return vt.size();
}
```

背包
```cpp
// 01背包刚好装满，初始化f[0]为1，表示不选择任何物品的情况下，容量为0时方法数为1，容量大于0时方法数为0（不可能）
int f[k]; memset(f, 0, sizeof(f));
f[0] = 1;
for (auto w : a) {
    for (int i = k-1; i >= w; i--) {
        f[i] += f[i-w];
    }
}

// 01背包不超过容量，初始化全部为1，表示不选择任何物品的情况下，容量不超过i的方法数为1
int f[k]; fill(f, f+k, 1);
for (auto w : a) {
    for (int i = k-1; i >= w; i--) {
        f[i] += f[i-w];
    }
}
```

**lca**
最近公共祖先 倍增算法。先把深度大的点跳到同等深度（二进制枚举深度差往上跳），然后一起往上跳到lca（枚举最高位到最低位）
```cpp
int lca(int n, vector<vector<int>>& edges, int x, int y) {
    vector<vector<pii>> g(n);
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2] - 1;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    }

    int m = 32 - __builtin_clz(n);
    vector<int> depth(n, 0);
    vector<vector<int>> pa(n, vector<int>(m, -1));

    function<void(int, int, int)> dfs = [&](int x, int fa, int d) {
        pa[x][0] = fa, depth[x] = d;
        for (auto [y, w] : g[x]) {
            if (y != fa) dfs(y, x, d + 1);
        }
    };
    dfs(0, -1, 0);

    for (int i = 1; i < m; i++) {
        for (int x = 0; x < n; x++) {
            if (int p = pa[x][i - 1]; p != -1) pa[x][i] = pa[p][i - 1];
        }
    }

    if (depth[x] > depth[y]) swap(x, y);
    for (int k = depth[y] - depth[x]; k; k &= k - 1) {
        y = pa[y][__builtin_ctz(k)];
    }
    if (x != y) {
        for (int i = m - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) x = px, y = py;
        }
        x = y = pa[x][0];
    }
    return x;
}
```

**矩阵**
```cpp
using ll = long long;
struct matrix {
    ll n, m;
    vector<vector<ll>> a;

    matrix(ll n, ll m) : n(n), m(m), a(vector<vector<ll>>(n, vector<ll>(m))) {}
    matrix(vector<vector<ll>> v) : n(v.size()), m(v[0].size()), a(v) {}
};

matrix operator*(matrix &a, matrix &b) {
    matrix ans(a.n, b.m);
    for (int i = 0; i < ans.n; i++) {
        for (int j = 0; j < ans.m; j++) {
            for (int k = 0; k < a.m; k++) {
                (ans.a[i][j] += a.a[i][k] * b.a[k][j]) %= mod;
            }
        }
    }
    return ans;
}

matrix pow(matrix a, ll n) {
    matrix ans({{1, 0}, {0, 1}});
    for (; n; n >>= 1, a = a * a) if (n & 1) ans = ans * a;
    return ans;
}

void f() {
    matrix mt({{1, 2}, {3, 4}}); mt = pow(mt, 1e8);
    matrix a0({{0, 1}}); a0 = a0 * mt;
}
```

 **数位DP (digit）**
状态：dp[i][x] - 前i位（从最高位开始算）当状态为x（比如最后一位的数字为x）时候的答案个数
转移：1）当前不含数字时，可以继续不填数字，直接进入下一位，2）枚举下一位的满足条件的数字y，sum(dp[i+1][y])
```cpp
int f(int n) {
    string s = to_string(n);
    int m = s.size(), dp[m][xxx];
    memset(dp, -1, sizeof(dp));

    function<int(int, int, bool, bool)> f = [&](int i, int pre, bool islimit, bool isnum) -> int {
        if (i == m) return 1; // 0也合法，如果要排除0返回isnum
        if (!islimit && isnum && dp[i][pre] != -1) return dp[i][pre];
        int ans = 0;
        if (!isnum) ans += f(i+1, pre, false, false); // limit为false，因为前一位填了前导0
        for (int d = 1-isnum, up = islimit ? s[i]-'0' : 9; d <= up; d++) {
            if (xxx) ans += f(i+1, d, islimit && d==up, true);
        }
        if (!islimit && isnum) dp[i][pre] = ans;
        return ans;
    };
    return f(0, 0, true, false);
}

int countDigitOne(int n) { // 1-n有几个数字1
    string s = to_string(n);
    int m = s.size(), dp[m][m]; // dp[i][j]: 前i位1出现了j次的数字的个数
    memset(dp, -1, sizeof(dp));

    function<int(int, int, bool)> f = [&](int i, int cnt, bool limit) {
        if (i == m) return cnt;
        if (!limit && dp[i][cnt] != -1) return dp[i][cnt];
        int ans = 0;
        for (int d = 0, up = limit ? s[i]-'0' : 9; d <= up; d++) {
            ans += f(i + 1, cnt + (d == 1), limit && d == up);
        }
        if (!limit) dp[i][cnt] = ans;
        return ans;
    };
    return f(0, 0, true);
}
```

**随机数**
```cpp
mt19937 Rnd(random_device{}());    //随机数生成器
uniform_int_distribution<int> dist1(0,100); //0——100的随机整数
uniform_real_distribution<double> dist2(-10,10); //-10——10的随机浮点数
cout << dist1(Rnd) << dist2(Rnd) <<endl;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
```

**从数据范围估计算法复杂度**
```
- 20：指数
- 40：折半然后指数
- 1e2：O(n^3)
- 1e3：O(n^2) O(n^2logn)
- 1e4：O(n^2)
- 1e5：O(nlogn)
- 1e9：O(n) O(logn)
- 1e18：O(logn)
```
