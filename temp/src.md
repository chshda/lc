# 题解

## 3074. 重新分装苹果

给你一个长度为 n 的数组 apple 和另一个长度为 m 的数组 capacity 。
一共有 n 个包裹，其中第 i 个包裹中装着 apple[i] 个苹果。同时，还有 m 个箱子，第 i 个箱子的容量为 capacity[i] 个苹果。
请你选择一些箱子来将这 n 个包裹中的苹果重新分装到箱子中，返回你需要选择的箱子的 最小 数量。
注意，同一个包裹中的苹果可以分装到不同的箱子中。

```cpp
class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int sum = accumulate(apple.begin(), apple.end(), 0);
        ranges::sort(capacity, greater<>());
        for (int i = 0; i < capacity.size(); i++) {
            sum -= capacity[i];
            if (sum <= 0) return i+1;
        }
        return -1;
    }
};
```

## 3075. 幸福值最大化的选择方案

给你一个长度为 n 的数组 happiness ，以及一个 正整数 k 。
n 个孩子站成一队，其中第 i 个孩子的 幸福值 是 happiness[i] 。你计划组织 k 轮筛选从这 n 个孩子中选出 k 个孩子。
在每一轮选择一个孩子时，所有 尚未 被选中的孩子的 幸福值 将减少 1 。注意，幸福值 不能 变成负数，且只有在它是正数的情况下才会减少。
选择 k 个孩子，并使你选中的孩子幸福值之和最大，返回你能够得到的 最大值 。

```cpp
using ll = long long;
class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        ranges::sort(happiness, greater<>());
        ll ans = 0;
        for (int i = 0; i < k; i++) ans += max(happiness[i] - i, 0);
        return ans;
    }
};
```

## 3076. 数组中的最短非公共子字符串

给你一个数组 arr ，数组中有 n 个 非空 字符串。
请你求出一个长度为 n 的字符串 answer ，满足：
answer[i] 是 arr[i] 最短 的子字符串，且它不是 arr 中其他任何字符串的子字符串。如果有多个这样的子字符串存在，answer[i] 应该是它们中字典序最小的一个。如果不存在这样的子字符串，answer[i] 为空字符串。
请你返回数组 answer 。

```cpp
class Solution {
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();
        auto ok = [&](int id, string s) {
            for (int i = 0; i < n; i++) if (i != id) {
                if (arr[i].find(s) != -1) return false;
            }
            return true;
        };

        vector<string> ans(n);
        for (int i = 0; i < n; i++) {
            string tans;
            auto s = arr[i];
            for (int len = 1; len <= s.size(); len++) {
                for (int st = 0; st < s.size(); st++) {                    
                    if (int ed = st + len - 1; ed >= s.size()) break;
                    string sub = s.substr(st, len);
                    if (ok(i, sub) && (tans.empty() || sub < tans)) tans = sub;
                }
                if (!tans.empty()) break;
            }
            ans[i] = tans;
        }
        return ans;
    }
};
```

## 3077. K 个不相交子数组的最大能量值

给你一个长度为 n 下标从 0 开始的整数数组 nums 和一个 正奇数 整数 k 。
x 个子数组的能量值定义为 strength = sum[1] * x - sum[2] * (x - 1) + sum[3] * (x - 2) - sum[4] * (x - 3) + ... + sum[x] * 1 ，其中 sum[i] 是第 i 个子数组的和。更正式的，能量值是满足 1 <= i <= x 的所有 i 对应的 (-1)^(i+1) * sum[i] * (x - i + 1) 之和。
你需要在 nums 中选择 k 个 不相交子数组 ，使得 能量值最大 。
请你返回可以得到的 最大能量值 。
注意，选出来的所有子数组 不 需要覆盖整个数组。

```cpp
using ll = long long;
class Solution {
public:
    long long maximumStrength(vector<int>& nums, int k) {
        // 划分型DP，第一维度划分个数，第二维度前缀长度
        // dp[i][j]，前j个数（0到j-1）取i个子数组 最大能量，i必须<= j
        // dp[i][j] = max
        //     第j个数不取：dp[i][j-1]
        //     第j个数取，枚举这个区间左端点下标k取最大值 dp[i-1][k] + sum(k,j-1) * w
        //               区间和转化为前缀和，pre(j) - pre(k)，pre下标1based
        //               提取出不变量 pre[j]*w + max(dp[i-1][k] - pre[k]*w)
        //               k取值范围 最大j-1只取一个数 最小i-1
        //                        注意到这个范围下限不变，可以用一个变量存储最大值
        //                              (假如下限也是单调递增变化，可以使用单调队列优化)
        // 初始化 第一维度i递减 当i为0时 值为0，dp[0][*] = 0
        //       第二维度j递减，边界条件dp[i][i-1]，不可能取到，为-oo
        // w取值 符号 - i是奇数时为1否则为-1 权重-（不变量=划分下标+权重=1+k）= k+1-i
        
        int n = nums.size();      
        vector<ll> pre(n+1);
        for (int i = 1; i <= n; i++) pre[i] = pre[i-1] + nums[i-1];

        vector<vector<ll>> f(k+1, vector<ll>(n+1));
        for (int i = 1; i <= k; i++) {
            f[i][i-1] = LLONG_MIN;
            ll w = (i % 2 ? 1 : -1) * (k + 1 - i);
            ll mx = LLONG_MIN;            
            for (int j = i; j <= n; j++) {
                mx = max(mx, f[i-1][j-1] - pre[j-1] * w);
                f[i][j] = max(f[i][j-1], pre[j]*w + mx);
            }
        }
        return f[k][n];
    }
};
```

## 3083. 字符串及其反转中是否存在同一子字符串

给你一个字符串 s ，请你判断字符串 s 是否存在一个长度为 2 的子字符串，在其反转后的字符串中也出现。
如果存在这样的子字符串，返回 true；如果不存在，返回 false 。

```cpp
class Solution {
public:
    bool isSubstringPresent(string s) {
        auto t = s;
        ranges::reverse(t);
        for (int i = 0; i < s.size()-1; i++) {
            if (t.find(s.substr(i, 2)) != -1) return true;
        }
        return false;
    }
};
```

## 3084. 统计以给定字符开头和结尾的子字符串总数

给你一个字符串 s 和一个字符 c 。返回在字符串 s 中并且以 c 字符开头和结尾的非空子字符串的总数。

```cpp
class Solution {
public:
    long long countSubstrings(string s, char c) {
        long long k = ranges::count(s, c);
        return k * (k + 1) / 2;
    }
};
```

## 3085. 成为 K 特殊字符串需要删除的最少字符数

给你一个字符串 word 和一个整数 k。
如果 |freq(word[i]) - freq(word[j])| <= k 对于字符串中所有下标 i 和 j  都成立，则认为 word 是 k 特殊字符串。
此处，freq(x) 表示字符 x 在 word 中的出现频率，而 |y| 表示 y 的绝对值。
返回使 word 成为 k 特殊字符串 需要删除的字符的最小数量。

```cpp
class Solution {
public:
    int minimumDeletions(string word, int k) {
        int c[26]{};
        for (auto i : word) c[i-'a']++;

        int left = 0;
        for (int i = 0; i < 26; i++) { // 枚举剩下的数里最小的那个
            int sum = 0;
            for (auto j : c) {
                if (j >= c[i]) sum += min(j, c[i]+k);
            }
            left = max(left, sum);
        }
        return word.size() - left;
    }
};
```

## 3086. 拾起 K 个 1 需要的最少行动次数

给你一个下标从 0 开始的二进制数组 nums，其长度为 n ；另给你一个 正整数 k 以及一个 非负整数 maxChanges 。

Alice 在玩一个游戏，游戏的目标是让 Alice 使用 最少 数量的 行动 次数从 nums 中拾起 k 个 1 。游戏开始时，Alice 可以选择数组 [0, n - 1] 范围内的任何索引 aliceIndex 站立。如果 nums[aliceIndex] == 1 ，Alice 会拾起一个 1 ，并且 nums[aliceIndex] 变成0（这 不算 作一次行动）。之后，Alice 可以执行 任意数量 的 行动（包括零次），在每次行动中 Alice 必须 恰好 执行以下动作之一：

选择任意一个下标 j != aliceIndex 且满足 nums[j] == 0 ，然后将 nums[j] 设置为 1 。这个动作最多可以执行 maxChanges 次。
选择任意两个相邻的下标 x 和 y（|x - y| == 1）且满足 nums[x] == 1, nums[y] == 0 ，然后交换它们的值（将 nums[y] = 1 和 nums[x] = 0）。如果 y == aliceIndex，在这次行动后 Alice 拾起一个 1 ，并且 nums[y] 变成 0 。
返回 Alice 拾起 恰好 k 个 1 所需的 最少 行动次数。

```cpp
using ll = long long;
class Solution {
public:
    long long minimumMoves(vector<int>& nums, int k, int maxChanges) {
        vector<int> pos;
        int mx = 0, cur = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                cur = 0;
            } else {
                cur += 1, mx = max(mx, cur);
                pos.push_back(i);
            }
        }
        mx = min(min(mx, 3), k); // 连续的1的长度，不超过3和k，这里的1可以快速获得
        if (maxChanges >= k - mx) {
            return (k - mx) * 2 + max(mx - 1, 0); // mx之外的1通过生成1再交换获得
        }

        n = pos.size();
        vector<ll> pre(n+1);
        for (int i = 1; i <= n; i++) pre[i] = pre[i-1] + pos[i-1];

        ll ans = LLONG_MAX;
        int len = k - maxChanges;
        for (int st = 0; st < n; st++) { // 枚举区间，区间里的通过交换移动获得，剩下的通过生成1再交换获得
            int ed = st + len - 1;
            if (ed >= n) break;
            int md = (st + ed) >> 1;
            ll val = pos[md];
            ll v1 = val * (md - st) - (pre[md+1] - pre[st]);
            ll v2 = (pre[ed+1] - pre[md]) - val * (ed - md);
            ans = min(ans, v1 + v2);
        }
        return ans + maxChanges * 2;
    }
};
```

## 3090. 每个字符最多出现两次的最长子字符串

给你一个字符串 s ，请找出满足每个字符最多出现两次的最长子字符串，并返回该子字符串的 最大 长度。

```cpp
class Solution {
public:
    int maximumLengthSubstring(string s) {
        int ans = 1;
        unordered_map<int, int> m;
        for (int i = 0, j = 0; i < s.size(); i++) {
            if (++m[s[i]] > 2) {
                while (j < i) {
                    if (--m[s[j++]] == 2) break;
                }
            }
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
```

## 3091. 执行操作使数据元素之和大于等于 K

给你一个正整数 k 。最初，你有一个数组 nums = [1] 。

你可以对数组执行以下 任意 操作 任意 次数（可能为零）：

选择数组中的任何一个元素，然后将它的值 增加 1 。
复制数组中的任何一个元素，然后将它附加到数组的末尾。
返回使得最终数组元素之 和 大于或等于 k 所需的 最少 操作次数。

```cpp
class Solution {
public:
    int minOperations(int k) {
        int ans = INT_MAX;
        for (int i = 0; i <= k; i++) {
            int j = (k + i) / (i + 1) - 1;
            ans = min(ans, i + j);
        }
        return ans;
    }
};
```

## 3092. 最高频率的 ID

你需要在一个集合里动态记录 ID 的出现频率。给你两个长度都为 n 的整数数组 nums 和 freq ，nums 中每一个元素表示一个 ID ，对应的 freq 中的元素表示这个 ID 在集合中此次操作后需要增加或者减少的数目。

增加 ID 的数目：如果 freq[i] 是正数，那么 freq[i] 个 ID 为 nums[i] 的元素在第 i 步操作后会添加到集合中。
减少 ID 的数目：如果 freq[i] 是负数，那么 -freq[i] 个 ID 为 nums[i] 的元素在第 i 步操作后会从集合中删除。
请你返回一个长度为 n 的数组 ans ，其中 ans[i] 表示第 i 步操作后出现频率最高的 ID 数目 ，如果在某次操作后集合为空，那么 ans[i] 为 0 。

```cpp
using ll = long long;
class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {                
        int n = nums.size();
        vector<ll> ans(n);

        unordered_map<ll, ll> m;
        multiset<ll> s;        
        for (int i = 0; i < n; i++) {
            auto &c = m[nums[i]];
            if (s.contains(c)) s.erase(s.find(c));
            c += freq[i];
            s.insert(c);
            ans[i] = *s.rbegin();
        }
        return ans;
    }
};
```

## 3093. 最长公共后缀查询

给你两个字符串数组 wordsContainer 和 wordsQuery 。

对于每个 wordsQuery[i] ，你需要从 wordsContainer 中找到一个与 wordsQuery[i] 有 最长公共后缀 的字符串。如果 wordsContainer 中有两个或者更多字符串有最长公共后缀，那么答案为长度 最短 的。如果有超过两个字符串有 相同 最短长度，那么答案为它们在 wordsContainer 中出现 更早 的一个。

请你返回一个整数数组 ans ，其中 ans[i]是 wordsContainer中与 wordsQuery[i] 有 最长公共后缀 字符串的下标。

```cpp
mt19937 gen(random_device{}());
int rnd(int x, int y) { return uniform_int_distribution<int>(x, y)(gen); }

struct SH1 {
    int n, mod, base;
    vector<long long> p, h;

    SH1(string &s, int mod = 998244353, int base = 131) : n(s.size()), mod(mod), base(base) {
        p.resize(n+1, 1);
        for (long long i = 1; i <= n; i++) p[i] = p[i-1] * base % mod;

        h.resize(n+1, 0);
        for (long long i = 0; i < n; i++) h[i+1] = (h[i] * base + s[i] - 'a' + 1) % mod;
    }

    long long hash(int i, int j) {  // [i, j], 0 based
        return (h[j+1] - h[i] * p[j - i + 1] % mod + mod) % mod;
    }
};

struct SH2 {
    int m1 = 998244353 + rnd(0, 1e9), b1 = 233 + rnd(0, 1e3);
    int m2 = 998244353 + rnd(0, 1e9), b2 = 233 + rnd(0, 1e3);

    int n;
    SH1 h1, h2;

    SH2(string &s) : n(s.size()), h1(SH1(s, m1, b1)), h2(SH1(s, m2, b2)) {}

    long long hash() { return hash(0, n - 1); }

    long long hash(int l, int r) {  // [i, j], 0 based
        return h1.hash(l, r) * m1 + h2.hash(l, r);
    }
};


using ll = long long;

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        int len = 0;
        for (auto &s : wordsContainer) len = max(len, (int)s.size());
        for (auto &s : wordsQuery) len = max(len, (int)s.size());
        unordered_map<ll, int> m[len+1];

        for (int i = 0; i < wordsContainer.size(); i++) {
            auto s = wordsContainer[i];
            SH1 sh(s);
            for (int j = 0; j < s.size(); j++) {
                ll k = s.size()-1 - j + 1, val = sh.hash(j, s.size()-1);                
                if (m[k].contains(val)) {
                    auto &v = m[k][val];
                    if (s.size() < wordsContainer[v].size()) v = i;                
                } else {
                    m[k][val] = i;
                }
            }
        }

        int mn = 0;
        for (int i = 1; i < wordsContainer.size(); i++) if (wordsContainer[i].size() < wordsContainer[mn].size()) mn = i;

        vector<int> ans;
        for(auto &q : wordsQuery) {
            SH1 hq(q);
            ll tans = mn;
            for (int i = 0; i < q.size(); i++) {
                ll k = q.size()-1 - i + 1, h = hq.hash(i, q.size()-1);                
                if (m[k].contains(h)) { tans = m[k][h]; break; }
            }
            ans.push_back(tans);
        }
        return ans;
    }
};
```