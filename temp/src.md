# 题解

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