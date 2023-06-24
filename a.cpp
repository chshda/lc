typedef long long ll;
typedef pair<int, int> pii;

vector<int> a(100);
sort(a.begin(), a.end());
sort(a.begin(), a.end(), greater<int>());
sort(a.begin(), a.end(), [&](auto &a, auto &b) { return a[0] < b[0]; });

__builtin_popcount


// 去除前导0
ans.erase(0, ans.find_first_not_of('0'));

// 去除重复元素，不需要已经排序，连续的重复数字只会保留一个
a.resize(unique(a.begin(), a.end()) - a.begin())


mt19937 Rnd(random_device{}());    //随机数生成器
uniform_int_distribution<int> dist1(0,100);    //定义dist1为0——100的随机整数
uniform_real_distribution<double> dist2(-10,10);    //定义dist2为-10——10的随机浮点数
cout<<dist1(Rnd)<<endl;    //输出随机数
cout<<dist2(Rnd)<<endl;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

lower_bound和upper_bound
没有自定义比较函数时：
* lower_bound：大于或等于目标的第一个数字
* upper_bound：大于目标的第一个数字

有自定义比较函数时：
* upper_bound：满足条件的第一个数字，(a.begin(), a.end(), x, [&](int tar, const auto &x) { return x.back() >= tar; });
    默认cmp为>，效果是 满足条件，即大于 的第一个数字
* lower_bound：不满足条件的第一个数字，(a.begin(), a.end(), x, [&](const auto &x, int tar) {return x.back() < tar; });
    默认cmp为<，效果是 不满足<条件，即大于或等于 的第一个数字
    
lower_bound中cmp本类型出现在第一个参数（目标类型在第二个参数），upper_bound中cmp出现在第二个参数，即lower第一，upper第二
        
// accumulate(a.begin(), a.end(), 0);
// iota(a.begin(), a.end(), 0);
// *max_element(a.begin(), a.end());
//
// auto f = [](int total, string s) { return total + s.size() + 1; ;
// accumulate(a.begin(), a.end(), 0, f);

// lower_bound(a.begin(), a.end(), x);
// lower_bound(a.begin(), a.end(), x, [&](auto &a, int v) { return a[0] < v; });

// ceil(a); floor(a);

// unordered_set<int> s(a.begin(), a.end());
// for (auto &[k, v] : myMap) {}

// function<int(int, int)> gcd = [&](auto &a, auto &b) { return b == 0 ? a : gcd(b, a % b); };

// int a[n]; iota(a, a+n, 0);
// int a[n]; memset(a, -1, sizeof(a)); // 0x3f

// vector<int> nums; // 待离散化
// vector<int> t = nums;
// sort(t.begin(), t.end());
// t.erase(unique(t.begin(), t.end()), t.end());
// for (auto &i : nums) i = lower_bound(t.begin(), t.end(), i) - t.begin() + 1;

// 二分查找，[l, r]区间内满足条件的最小值
void bin1(int l, int r) {
    while (l < r) {
        int m = l + r >> 1;
        if (ok(m)) r = m;
        else l = m + 1;
    }
}

// 优先队列 - 比较函数里优先值高的会尽量被保存在队里，优先值低的会被先pop掉
auto cmp = [&](psi &a, psi &b) { return a.second > b.second || (a.second == b.second && a < b); };
priority_queue<psi, vector<psi>, decltype(cmp)> q(cmp);

deque<int> q;
q.front(); q.push_front(); q.emplace_front(); q.pop_front();
q.back(); q.push_back(); q.emplace_back(); q.pop_back();

vector<int> a;
make_heap(a.begin(), a.end(), greater<int>()); // 最大的优先，保留在数组里，最小的会被先pop掉
pop_heap(a.begin(), a.end(), greater<int>()); a.pop();
a.push_back(1); push_heap(a.begin(), a.end(), greater<int>());

// 前缀和
// int s[n]; s[0] = 0; partial_sum(a.begin(), a.end(), s + 1);
// sum[a, b] = sum[a, c) = s[c] - s[a];

// 分解质因数
vector<int> primeFactorization(int num) {
    vector<int> ans;
    int up = (int)sqrt(num) + 1;
    for (int i = 2; i < up; ++i) {
        while (num % i == 0) {
            num /= i;
            ans.push_back(i);
        }
    }
    if (num != 1) { ans.push_back(num); }
    return ans;
}

class BIT {
public:
    BIT(int nn): n(nn), c(nn + 1, 0) {}

    int lowbit(int x) { return x & (-x); }

    void update(int i, int val = 1) {
        while (i <= n) c[i] += val, i += lowbit(i);
    }

    int sum(int i) {
        int ans = 0;
        while (i) ans += c[i], i -= lowbit(i);
        return ans;
    }

    int query(int l, int r) { return sum(r) - sum(l - 1); }

private:
    vector<int> c; // 数组下标从1开始
    int n;
};

// 并查集
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
  
// 最短路算法
void buildGraph() {
    vector<vector<pair<int, int>>> g(n);
    for (auto &e : edges) {
        int u = e[0], v = e[1], d = e[2];
        g[u].emplace_back(v, d); g[v].emplace_back(u, d);
    }
}
    
vector<int> dijkstra(const vector<vector<pii>> &g, int n, int start) {
    vector<int> dis(n, INT_MAX); dis[start] = 0;
    priority_queue<pii, vector<pii>, greater<>> q; q.emplace(0, start);
    while (!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (d > dis[x]) continue;
        for (auto [y, nd] : g[x]) {
            nd += d;
            if (nd < dis[y]) { dis[y] = nd; q.emplace(nd, y); }
        }
    }
    return dis;
}

// 最短路 - 堆优化
int dijkstra(const vector<vector<pii>> &g, int n, int start, int end) {
    vector<int> dis(n, INT_MAX); dis[start] = 0;
    priority_queue<pii, vector<pii>, greater<>> q; q.emplace(0, start);
    while(!q.empty()) {
        auto [d, x] = q.top(); q.pop();
        if (x == end) return d;
        if (d > dis[x]) continue;
        for (auto [y, nd] : g[x]) {
            nd += d;
            if (nd < dis[y]) { dis[y] = nd; q.emplace(nd, y); }
        }
    }
    return -1;
}

// 最短路 - 朴素算法
int dijkstra(const vector<vector<pii>> &g, int n, int start, int end) {
    vector<int> dis(n, INT_MAX), vs(n, false);
    dis[start] = 0;
    while (true) {
        int mn = -1;
        for (int i = 0; i < n; i++) {
            if (!vs[i] && (mn == -1 || dis[i] < dis[mn])) mn = i;
        }
        if (mn == -1 || dis[mn] == INT_MAX) return -1;
        if (mn == end) return dis[mn];
        vs[mn] = true;
        for (auto [y, w] : g[mn]) {
            if (dis[mn] + w < dis[y]) dis[y] = dis[mn] + w;
        }
    }
    return -1;
}   
    
// 最长上升子序列
int lengthOfLIS(vector<int>& a) {
    vector<int> vt;
    for (auto i : a) {
        if (vt.empty() || i > vt.back()) vt.push_back(i);
        else *lower_bound(vt.begin(), vt.end(), i) = i;
    }
    return vt.size();
}
    
// 数位dp 统计1的个数
// dp[i][j]:前i为中1出现了j次的数字的个数
int countDigitOne(int n) {
    string s = to_string(n);
    int m = s.size(), dp[m][m];
    memset(dp, -1, sizeof(dp));

    function<int(int, int, bool)> f = [&](int i, int cnt, bool limit) {
        if (i == m) return cnt; // 递归终止条件
        if (!limit && dp[i][cnt] != -1) return dp[i][cnt]; // 使用记忆结果
        int ans = 0;
        for (int d = 0, up = limit ? s[i]-'0' : 9; d <= up; d++) { // 枚举每个数字，注意limit的情况
            ans += f(i + 1, cnt + (d == 1), limit && d == up);
        }
        if (!limit) dp[i][cnt] = ans; // 记忆结果
        return ans;
    };
    return f(0, 0, true);
}
    

// kmp算法 t中找p
int kmp(string t, string p) {
    int n = t.size(), m = p.size(), next[m+1];

    next[0] = -1;
    int i = 0, j = -1;
    while (i < m) {
        if (j == -1 || p[i] == p[j]) next[++i] = ++j;
        else j = next[j];
    }

    i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || t[i] == p[j]) i++, j++;
        else j = next[j];
    }
    return j == m ? i - j : -1;
}
    
// Trie树
// class Trie {
// public:
//     Trie() : root(new Node()) { }
//     void insert(string word) {
//         Node *p = root;
//         for (auto &ch : word) {
//             int i = ch - 'a';
//             if (p->children[i] == nullptr) p->children[i] = new Node();
//             p = p->children[i];
//         }
//         p->isEnd = true;
//     }    
//     bool search(string word) {
//         Node *p = root;
//         for (auto &ch : word) {
//             int i = ch - 'a';
//             if (p->children[i] == nullptr) return false;
//             p = p->children[i];
//         }
//         return p->isEnd;
//     }
//     bool startsWith(string prefix) {
//         Node *p = root;
//         for (auto &ch : prefix) {
//             int i = ch - 'a';
//             if (p->children[i] == nullptr) return false;
//             p = p->children[i];
//         }
//         return true;
//     }
// private:
//     struct Node { bool isEnd; Node *children[26]; };
//     Node *root;
// };

// 动态开点线段树，使用map模拟数组，不需要提前构建整棵树，需要的时候才往map中添加点
class MyCalendar {
    unordered_map<int, pii> mp;

    bool query(int id, int l, int r, int L, int R) {
        if (r < L || l > R) return false;

        auto [has, lazy] = mp[id];
        if (lazy) return true;
        if (l >= L && r <= R) return has;

        int m = l + r >> 1, idl = id << 1, idr = idl + 1;
        return query(idl, l, m, L, R) || query(idr, m+1, r, L, R);
    }

    void update(int id, int l, int r, int L, int R) {
        if (r < L || l > R) return;
        if (l >= L && r <= R) { mp[id] = {true, true}; return; }

        int m = l + r >> 1, idl = id << 1, idr = idl + 1;
        update(idl, l, m, L, R);
        update(idr, m+1, r, L, R);
        mp[id] = {mp[idl].first || mp[idr].first, false};
    }
    
    bool book(int start, int end) {
        if (query(1, 0, 1e9, start, end-1)) return false;
        update(1, 0, 1e9, start, end-1); return true;
    }
};                              
          
//                                   https://www.cnblogs.com/Leocsse/p/16789621.html
//                                   const int N = 1e6;

// struct node {
//     int l, r;
//     long long sum, add;
// }tr[N * 4];

// class Solution {
// public:
//     vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
//         n = nums1.size();
//         for (int i = 1; i <= n; i++) w[i] = nums1[i-1];

//         build(1, 1, n);

//         vector<long long> ans;
//         long long t = 0;
//         for (int i = 0; i < n; i++) t += nums2[i];
        
//         for (int i = 0; i < queries.size(); i++) {
//             auto q = queries[i];
//             if (q[0] == 1) {
//                 int l = q[1] + 1, r = q[2] + 1;
//                 modify(1, l, r);
                
//             } else if (q[0] == 2) {                
//                 t += query(1, 1, n) * q[1];
//             } else {
//                 ans.push_back(t);
//             }
//         }
//         return ans;
//     }
    
//     void pushup(int u) {
//         tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
//     }

//     void pushdown(int u) {
//         auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
//         if (root.add % 2 == 1) {
//             left.add += root.add, left.sum = (long long)(left.r - left.l + 1) - left.sum;
            
//             right.add += root.add, right.sum = (long long)(right.r - right.l + 1) - right.sum;            
//         }
//         root.add = 0;
//     }

//     void build(int u, int l, int r) {
//         if (l == r) tr[u] = {l, r, w[l], 0};
//         else {
//             tr[u] = {l, r};
//             int mid = l + r >> 1;
//             build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
//             pushup(u);
//         }
//     }

//     void modify(int u, int l, int r) {
//         if (tr[u].l >= l && tr[u].r <= r) {
//             tr[u].sum = (long long)(tr[u].r - tr[u].l + 1) - tr[u].sum;
//             tr[u].add += 1;
//         }
//         else {
//             pushdown(u);
//             int mid = tr[u].l + tr[u].r >> 1;
//             if (l <= mid) modify(u << 1, l, r);
//             if (r > mid) modify(u << 1 | 1, l, r);
//             pushup(u);
//         }
//     }

//     long long query(int u, int l, int r) {
//         if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;

//         pushdown(u);
//         int mid = tr[u].l + tr[u].r >> 1;
//         long long ans = 0;
//         if (l <= mid) ans = query(u << 1, l, r);
//         if (r > mid) ans += query(u << 1 | 1, l, r);
//         return ans;
//     }
    
// private:
//     int n;
//     int w[N];
// };
    
    经典题目：
        最短路，最短路的数量，
        
        
求第k小，二分答案，判定ok：找出小于或者等于x的数量，这个数量必须大于等于k，二分这个满足这个条件的最小值

