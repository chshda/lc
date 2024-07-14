# 题解

## 第 375 场周赛

### 2963. 统计好分割方案的数目

给你一个下标从 0 开始、由 正整数 组成的数组 nums。

将数组分割成一个或多个 连续 子数组，如果不存在包含了相同数字的两个子数组，则认为是一种 好分割方案 。

返回 nums 的 好分割方案 的 数目。

由于答案可能很大，请返回答案对 109 + 7 取余 的结果。

```cpp
// 2 ^ (m-1)
static const int mod = 1e9 + 7;
class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        unordered_map<int, int> r;
        for (int i = 0; i < nums.size(); i++) r[nums[i]] = i;

        int cnt = 0;
        for (int i = 0, j = 0; i < nums.size(); i++) {
            j = max(j, r[nums[i]]);
            if (i == j) cnt++;
        }
        long long ans = 1;
        while (--cnt) ans = ans * 2 % mod;
        return ans;
    }
};
```

## 第 376 场周赛

### 2968. 执行操作使频率分数最大

给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。

你可以对数组执行 至多 k 次操作：

从数组中选择一个下标 i ，将 nums[i] 增加 或者 减少 1 。

最终数组的频率分数定义为数组中众数的 频率 。

请你返回你可以得到的 最大 频率分数。

众数指的是数组中出现次数最多的数。一个元素的频率指的是数组中这个元素的出现次数。


```cpp
class Solution {
public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        int n = nums.size(), st = 1, ed = n;

        ranges::sort(nums);
        vector<long long> pre(n + 1);
        for (int i = 0; i < n; i++) pre[i+1] = pre[i] + nums[i];

        auto ok = [&](int x) {
            for (int i = x-1; i < n; i++) {
                int st = i - (x - 1), ed = i;
                int md = (st + ed) >> 1;
                long long need = (md - st + 1LL) * nums[md] - (pre[md+1] - pre[st]) + (pre[ed+1] - pre[md]) - (ed - md + 1LL) * nums[md];
                if (need <= k) return true;
            }
            return false;
        };

        while (st < ed) {
            int md = (st + ed + 1) >> 1;
            if (ok(md)) st = md;
            else ed = md - 1;
        }
        return st;
    }
};
```

## 第 377 场周赛

### 2977. 转换字符串的最小成本 II

给你两个下标从 0 开始的字符串 source 和 target ，它们的长度均为 n 并且由 小写 英文字母组成。

另给你两个下标从 0 开始的字符串数组 original 和 changed ，以及一个整数数组 cost ，其中 cost[i] 代表将字符串 original[i] 更改为字符串 changed[i] 的成本。

你从字符串 source 开始。在一次操作中，如果 存在 任意 下标 j 满足 cost[j] == z  、original[j] == x 以及 changed[j] == y ，你就可以选择字符串中的 子串 x 并以 z 的成本将其更改为 y 。 你可以执行 任意数量 的操作，但是任两次操作必须满足 以下两个 条件 之一 ：

* 在两次操作中选择的子串分别是 source[a..b] 和 source[c..d] ，满足 b < c  或 d < a 。换句话说，两次操作中选择的下标 不相交 。
* 在两次操作中选择的子串分别是 source[a..b] 和 source[c..d] ，满足 a == c 且 b == d 。换句话说，两次操作中选择的下标 相同 。

返回将字符串 source 转换为字符串 target 所需的 最小 成本。如果不可能完成转换，则返回 -1 。

注意，可能存在下标 i 、j 使得 original[j] == original[i] 且 changed[j] == changed[i] 。



## 第 378 场周赛

### 2983. 回文串重新排列查询

给你一个长度为 偶数 n ，下标从 0 开始的字符串 s 。

同时给你一个下标从 0 开始的二维整数数组 queries ，其中 queries[i] = [ai, bi, ci, di] 。

对于每个查询 i ，你需要执行以下操作：

* 将下标在范围 0 <= ai <= bi < n / 2 内的 子字符串 s[ai:bi] 中的字符重新排列。
* 将下标在范围 n / 2 <= ci <= di < n 内的 子字符串 s[ci:di] 中的字符重新排列。

对于每个查询，你的任务是判断执行操作后能否让 s 变成一个 回文串 。

每个查询与其他查询都是 独立的 。

请你返回一个下标从 0 开始的数组 answer ，如果第 i 个查询执行操作后，可以将 s 变为一个回文串，那么 answer[i] = true，否则为 false 。

子字符串 指的是一个字符串中一段连续的字符序列。s[x:y] 表示 s 中从下标 x 到 y 且两个端点 都包含 的子字符串。

```cpp
// 分类讨论
class Solution {
public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int m = s.size(), n = m / 2;
        string s1 = s.substr(0, n), s2 = s.substr(n);
        reverse(s2.begin(), s2.end());

        vector<vector<int>> pre1(n+1, vector<int>(26)); // 统计每个字母个数的前缀和 前i位中字母j出现的次数
        for (int i = 0; i < n; i++) pre1[i+1] = pre1[i], pre1[i+1][s1[i]-'a']++;

        vector<vector<int>> pre2(n+1, vector<int>(26));
        for (int i = 0; i < n; i++) pre2[i+1] = pre2[i], pre2[i+1][s2[i]-'a']++;

        vector<int> pre(n+1); // 统计不相等字母个数的前缀和
        for (int i = 0; i < n; i++) pre[i+1] = pre[i] + (s1[i] != s2[i]);

        auto count = [&](int l, int r, vector<vector<int>> &pre) {
            auto ans = pre[r+1]; // - pre[l]
            for (int i = 0; i < 26; i++) ans[i] -= pre[l][i];
            return ans;
        };

        auto subtract = [&](vector<int> a1, vector<int> a2) -> vector<int> {
            auto ans = a1;
            for (int i = 0; i < a1.size(); i++) {
                ans[i] -= a2[i];
                if (ans[i] < 0) return {};
            }
            return ans;
        };

        auto check = [&](int l1, int r1, int l2, int r2, vector<vector<int>> &pre1, vector<vector<int>> &pre2) {
            // [0, l1-1], [max(r1, r2)+1, n-1]
            cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
            if (pre[l1-1+1] - pre[0] > 0 || pre[n-1+1] - pre[max(r1, r2)+1] > 0) return false;

            if (l2 <= r1) {
                if (r2 <= r1) { // 包含 l1 l2 r2 r1，只要s1包含s2即可重排得到回文串
                    return count(l1, r1, pre1) == count(l1, r1, pre2);
                } else { // 相交 l1 l2 r1 r2
                    // [l1,            r1][r1+1,  r2]
                    // [l1,  l2-1] [l2            r2]
                    // l1,r1这个大段包含l1,l2-1这个小段的所有的字母
                    // l2,r2这个大段包含r1+1，r2这个小段的所有字母
                    // 并且相减后剩下的字母个数vector一致即可
                    auto a1 = subtract(count(l1, r1, pre1), count(l1, l2-1, pre2));
                    auto a2 = subtract(count(l2, r2, pre2), count(r1+1, r2, pre1));
                    return !a1.empty() && !a2.empty() && a1 == a2;
                }

            } else { // 不相交, l1, r1, l2, r2 // 只要中间段一一对应 前后字母统计个数相同即可
                // [r1+1, l2-1]
                if (pre[l2-1+1] - pre[r1+1] != 0) return false;
                // [l1, r1], [l2, r2]
                return count(l1, r1, pre1) == count(l1, r1, pre2) && count(l2, r2, pre1) == count(l2, r2, pre2);
            }
        };

        vector<bool> ans;
        for (auto &q : queries) {
            int l1 = q[0], r1 = q[1], l20 = q[2], r20 = q[3];
            int l2 = m - 1 - r20, r2 = m - 1 - l20;
            ans.push_back(l1 <= l2 ? check(l1, r1, l2, r2, pre1, pre2) : check(l2, r2, l1, r1, pre2, pre1));               
        }
        return ans;
    }
};
```

## 第 379 场周赛

### 3003. 执行操作后的最大分割数量

给你一个下标从 0 开始的字符串 s 和一个整数 k。

你需要执行以下分割操作，直到字符串 s 变为 空：

* 选择 s 的最长 前缀，该前缀最多包含 k 个 不同 字符。
* 删除 这个前缀，并将分割数量加一。如果有剩余字符，它们在 s 中保持原来的顺序。

执行操作之 前 ，你可以将 s 中 至多一处 下标的对应字符更改为另一个小写英文字母。

在最优选择情形下改变至多一处下标对应字符后，用整数表示并返回操作结束时得到的 最大 分割数量。

```cpp
using ll = long long;
class Solution {
public:
    string s;
    int k;
    unordered_map<ll, int> mm;

    // 到达第i个位置，之前的是mask和changed
    int dfs(int i, int mask, int changed) {
        if (i == s.size()) return 1;

        ll key = (ll)i << 32 | (ll) mask << 1 | changed;
        if (mm.contains(key)) return mm[key];

        int ans;
        int bit = (1 << (s[i] - 'a'));
        int new_mask = mask | bit;
        if (__builtin_popcount(new_mask) > k) {
            ans = dfs(i+1, bit, changed) + 1;
        } else {
            ans = dfs(i+1, new_mask, changed);
        }

        if (!changed) {
            for (int j = 0; j < 26; j++) {
                int new_mask = mask | (1 << j);
                if (__builtin_popcount(new_mask) > k) {
                    ans = max(ans, dfs(i+1, 1<<j, 1) + 1);
                } else {
                    ans = max(ans, dfs(i+1, new_mask, 1));
                }
            }
        }
        return mm[key] = ans;
    }

    int maxPartitionsAfterOperations(string ss, int kk) {
        s = ss, k = kk;
        mm.clear();
        return dfs(0, 0, 0);
    }
};
```

## 第 380 场周赛

### 3008. 找出数组中的美丽下标 II

给你一个下标从 0 开始的字符串 s 、字符串 a 、字符串 b 和一个整数 k 。

如果下标 i 满足以下条件，则认为它是一个 美丽下标 ：

* 0 <= i <= s.length - a.length
* s[i..(i + a.length - 1)] == a

存在下标 j 使得：

* 0 <= j <= s.length - b.length
* s[j..(j + b.length - 1)] == b
* |j - i| <= k

以数组形式按 从小到大排序 返回美丽下标。

```cpp
vector<int> kmp(string &text, string &pattern) {
    int m = pattern.length();
    vector<int> pi(m);
    int c = 0;
    for (int i = 1; i < m; i++) {
        char v = pattern[i];
        while (c && pattern[c] != v) {
            c = pi[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        pi[i] = c;
    }

    vector<int> res;
    c = 0;
    for (int i = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v) {
            c = pi[c - 1];
        }
        if (pattern[c] == v) {
            c++;
        }
        if (c == m) {
            res.push_back(i - m + 1);
            c = pi[c - 1];
        }
    }
    return res;
}

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        auto v1 = kmp(s, a);
        auto v2 = kmp(s, b);
        vector<int> ans;
        int j = 0, m = v2.size();
        for (auto i : v1) {
            while (j < m && v2[j] < i - k) j++;
            if (j < m && v2[j] <= i + k) ans.push_back(i);
        }
        return ans;        
    }
};
```


## 第 381 场周赛

### 3014. 输入单词需要的最少按键次数 I

给你一个字符串 word，由 不同 小写英文字母组成。

电话键盘上的按键与 不同 小写英文字母集合相映射，可以通过按压按键来组成单词。例如，按键 2 对应 ["a","b","c"]，我们需要按一次键来输入 "a"，按两次键来输入 "b"，按三次键来输入 "c"。

现在允许你将编号为 2 到 9 的按键重新映射到 不同 字母集合。每个按键可以映射到 任意数量 的字母，但每个字母 必须 恰好 映射到 一个 按键上。你需要找到输入字符串 word 所需的 最少 按键次数。

返回重新映射按键后输入 word 所需的 最少 按键次数。

下面给出了一种电话键盘上字母到按键的映射作为示例。注意 1，*，# 和 0 不 对应任何字母。

```cpp
// 同3016
```

### 3015. 按距离统计房屋对数目 I

给你三个 正整数 n 、x 和 y 。

在城市中，存在编号从 1 到 n 的房屋，由 n 条街道相连。对所有 1 <= i < n ，都存在一条街道连接编号为 i 的房屋与编号为 i + 1 的房屋。另存在一条街道连接编号为 x 的房屋与编号为 y 的房屋。

对于每个 k（1 <= k <= n），你需要找出所有满足要求的 房屋对 [house1, house2] ，即从 house1 到 house2 需要经过的 最少 街道数为 k 。

返回一个下标从 1 开始且长度为 n 的数组 result ，其中 result[k] 表示所有满足要求的房屋对的数量，即从一个房屋到另一个房屋需要经过的 最少 街道数为 k 。

注意，x 与 y 可以 相等 。

```cpp
```

### 3016. 输入单词需要的最少按键次数 II

给你一个字符串 word，由 不同 小写英文字母组成。

电话键盘上的按键与 不同 小写英文字母集合相映射，可以通过按压按键来组成单词。例如，按键 2 对应 ["a","b","c"]，我们需要按一次键来输入 "a"，按两次键来输入 "b"，按三次键来输入 "c"。

现在允许你将编号为 2 到 9 的按键重新映射到 不同 字母集合。每个按键可以映射到 任意数量 的字母，但每个字母 必须 恰好 映射到 一个 按键上。你需要找到输入字符串 word 所需的 最少 按键次数。

返回重新映射按键后输入 word 所需的 最少 按键次数。

下面给出了一种电话键盘上字母到按键的映射作为示例。注意 1，*，# 和 0 不 对应任何字母。

```cpp
class Solution {
public:
    int minimumPushes(string word) {
        vector<int> cnt(26);
        for (auto i : word) cnt[i-'a']++;
        ranges::sort(cnt, greater<>());
        int ans = 0;
        for (int i = 0, j = 1; i < 26; i++) {
            if (i > 0 && i % 8 == 0) j++;
            ans += j * cnt[i];            
        }
        return ans;
    }
};
```

## 第 382 场周赛

### 3019. 按键变更的次数

给你一个下标从 0 开始的字符串 s ，该字符串由用户输入。按键变更的定义是：使用与上次使用的按键不同的键。例如 s = "ab" 表示按键变更一次，而 s = "bBBb" 不存在按键变更。

返回用户输入过程中按键变更的次数。

注意：shift 或 caps lock 等修饰键不计入按键变更，也就是说，如果用户先输入字母 'a' 然后输入字母 'A' ，不算作按键变更。

```cpp
class Solution {
public:
    int countKeyChanges(string s) {
        int ans = 0;
        for (int i = 1; i < s.size(); i++) ans += tolower(s[i]) != tolower(s[i-1]);
        return ans;
    }
};
```

### 3020. 子集中元素的最大数量

给你一个 正整数 数组 nums 。

你需要从数组中选出一个满足下述条件的子集：

你可以将选中的元素放置在一个下标从 0 开始的数组中，并使其遵循以下模式：[x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x]（注意，k 可以是任何 非负 的 2 的幂）。例如，[2, 4, 16, 4, 2] 和 [3, 9, 3] 都符合这一模式，而 [2, 4, 8, 4, 2] 则不符合。

返回满足这些条件的子集中，元素数量的 最大值 。

```cpp
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> m;
        for (auto i : nums) m[i]++;

        int ans = m[1] - 1 | 1; // 将m[1]转化为奇数，m[1]为0时结果为-1，不影响后续求最大值
        m.erase(1);        
        for (auto [k0, v] : m) {
            int cnt = 0;
            long long k = k0;
            for (; m.contains(k) && m[k] >= 2; k *= k) cnt += 2; // 确保key存在时再读取，否则会插入这个元素
            ans = max(ans, cnt + (m.contains(k) ? 1 : -1));
        }
        return ans;
    }
};
```

### 3021. Alice 和 Bob 玩鲜花游戏

Alice 和 Bob 在一个长满鲜花的环形草地玩一个回合制游戏。环形的草地上有一些鲜花，Alice 到 Bob 之间顺时针有 x 朵鲜花，逆时针有 y 朵鲜花。

游戏过程如下：

* Alice 先行动。
* 每一次行动中，当前玩家必须选择顺时针或者逆时针，然后在这个方向上摘一朵鲜花。
* 一次行动结束后，如果所有鲜花都被摘完了，那么 当前 玩家抓住对手并赢得游戏的胜利。
  
给你两个整数 n 和 m ，你的任务是求出满足以下条件的所有 (x, y) 对：

* 按照上述规则，Alice 必须赢得游戏。
* Alice 顺时针方向上的鲜花数目 x 必须在区间 [1,n] 之间。
* Alice 逆时针方向上的鲜花数目 y 必须在区间 [1,m] 之间。
  
请你返回满足题目描述的数对 (x, y) 的数目。

```cpp
class Solution {
public:
    long long flowerGame(int n, int m) {
        long long a = (n + 1) / 2, b = n - a;
        long long c = (m + 1) / 2, d = m - c;
        return a * d + b * c;
    }
};
```

### 3022. 给定操作次数内使剩余元素的或值最小

给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。

一次操作中，你可以选择 nums 中满足 0 <= i < nums.length - 1 的一个下标 i ，并将 nums[i] 和 nums[i + 1] 替换为数字 nums[i] & nums[i + 1] ，其中 & 表示按位 AND 操作。

请你返回 至多 k 次操作以内，使 nums 中所有剩余元素按位 OR 结果的 最小值 。

```cpp
// 位运算，高位到低位处理，贪心尽量把高位变为0
// 处理到低位比如第2位时，同时考虑前面的高位和当前位，让他们都变成0，通过mask记录哪些位是可以变为0的
// 计算把几个数字变为0的操作次数时，如果一段子数组and为0，操作次数为n-1，如果and不为0，需要其他的一个0来额外变为0，操作次数位n
class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int ans = 0, mask = 0;
        for (int i = 29; i >= 0; i--) {
            mask |= 1 << i;
            int cnt = 0, and_res = -1;
            for (auto j : nums) {
                and_res &= j & mask;
                if (and_res == 0) and_res = -1;
                else cnt++;
            }
            if (cnt > k) ans |= 1 << i, mask ^= 1 << i;
        }        
        return ans;
    }
};
```

## 第 383 场周赛

### 3028. 边界上的蚂蚁

边界上有一只蚂蚁，它有时向 左 走，有时向 右 走。

给你一个 非零 整数数组 nums 。蚂蚁会按顺序读取 nums 中的元素，从第一个元素开始直到结束。每一步，蚂蚁会根据当前元素的值移动：

* 如果 nums[i] < 0 ，向 左 移动 -nums[i]单位。
* 如果 nums[i] > 0 ，向 右 移动 nums[i]单位。
* 
返回蚂蚁 返回 到边界上的次数。

注意：边界两侧有无限的空间。只有在蚂蚁移动了 |nums[i]| 单位后才检查它是否位于边界上。换句话说，如果蚂蚁只是在移动过程中穿过了边界，则不会计算在内。

```cpp
class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) {
        int ans = 0, sum = 0;
        for (auto i : nums) sum += i, ans += sum == 0;
        return ans;
    }
};
```

### 3029. 将单词恢复初始状态所需的最短时间 I

给你一个下标从 0 开始的字符串 word 和一个整数 k 。

在每一秒，你必须执行以下操作：

* 移除 word 的前 k 个字符。
* 在 word 的末尾添加 k 个任意字符。

注意 添加的字符不必和移除的字符相同。但是，必须在每一秒钟都执行 两种 操作。

返回将 word 恢复到其 初始 状态所需的 最短 时间（该时间必须大于零）。

```cpp
// Same as 3031.
```

### 3030. 找出网格的区域平均强度

给你一个下标从 0 开始、大小为 m x n 的网格 image ，表示一个灰度图像，其中 image[i][j] 表示在范围 [0..255] 内的某个像素强度。另给你一个 非负 整数 threshold 。

如果 image[a][b] 和 image[c][d] 满足 |a - c| + |b - d| == 1 ，则称这两个像素是 相邻像素 。

区域 是一个 3 x 3 的子网格，且满足区域中任意两个 相邻 像素之间，像素强度的 绝对差 小于或等于 threshold 。

区域 内的所有像素都认为属于该区域，而一个像素 可以 属于 多个 区域。

你需要计算一个下标从 0 开始、大小为 m x n 的网格 result ，其中 result[i][j] 是 image[i][j] 所属区域的 平均 强度，向下取整 到最接近的整数。如果 image[i][j] 属于多个区域，result[i][j] 是这些区域的 “取整后的平均强度” 的 平均值，也 向下取整 到最接近的整数。如果 image[i][j] 不属于任何区域，则 result[i][j] 等于 image[i][j] 。

返回网格 result 。

```cpp
class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        int m = image.size(), n = image[0].size();
        vector<vector<int>> sum(m, vector<int>(n)), cnt(m, vector<int>(n));

        auto f = [&](int x, int y) {
            for (int i = -1; i <= 1; i++) for (int j = -1; j <= 1; j++) {
                int x0 = x + i, y0 = y + j;
                for (int k = -1; k <= 1; k++) for (int l = -1; l <= 1; l++) {
                    int x1 = x + k, y1 = y + l;
                    if (abs(x0-x1) + abs(y0-y1) == 1 && abs(image[x0][y0] - image[x1][y1]) > threshold) return -1;
                }
            }
            int sum = 0;
            for (int i = -1; i <= 1; i++) for (int j = -1; j <= 1; j++) sum += image[x+i][y+j];
            return sum / 9;
        };

        for (int i = 1; i < m-1; i++) for (int j = 1; j < n-1; j++) {
                for (int dx = -1; dx <= 1; dx++) for (int dy = -1; dy <= 1; dy++) {
            if (int s = f(i, j); s != -1) {
                    sum[i+dx][j+dy] += s, cnt[i+dx][j+dy]++;
                }
            }
        }
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            if (cnt[i][j] == 0) sum[i][j] = image[i][j];
            else sum[i][j] /= cnt[i][j];
        }
        return sum;
    }
};
```

### 3031. 将单词恢复初始状态所需的最短时间 II

给你一个下标从 0 开始的字符串 word 和一个整数 k 。

在每一秒，你必须执行以下操作：

* 移除 word 的前 k 个字符。
* 在 word 的末尾添加 k 个任意字符。

注意 添加的字符不必和移除的字符相同。但是，必须在每一秒钟都执行 两种 操作。

返回将 word 恢复到其 初始 状态所需的 最短 时间（该时间必须大于零）。

```cpp
mt19937 gen(random_device{}());
int rnd(int x, int y) { return uniform_int_distribution<int>(x, y)(gen); }

int m1 = 998244353 + rnd(0, 1e9), b1 = 233 + rnd(0, 1e3);
int m2 = 998244353 + rnd(0, 1e9), b2 = 233 + rnd(0, 1e3);

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
    int n;
    SH1 h1, h2;

    SH2(string &s) : n(s.size()), h1(SH1(s, m1, b1)), h2(SH1(s, m2, b2)) {}

    long long hash() { return hash(0, n - 1); }

    long long hash(int l, int r) {  // [i, j], 0 based
        return h1.hash(l, r) * m1 + h2.hash(l, r);
    }
};

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        SH2 h(word);
        int n = word.size();
        for (int i = 1; i <= n; i++) {
            if ((long long)i * k > n) return i;
            if (h.hash(i * k, n - 1) == h.hash(0, n - 1 - i * k)) return i;
        }
        return -1;
    }
};
```

## 第 384 场周赛

### 3033. 修改矩阵

给你一个下标从 0 开始、大小为 m x n 的整数矩阵 matrix ，新建一个下标从 0 开始、名为 answer 的矩阵。使 answer 与 matrix 相等，接着将其中每个值为 -1 的元素替换为所在列的 最大 元素。

返回矩阵 answer 。

```cpp
class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for (int j = 0; j < n; j++) {
            int mx = -1;
            for (int i = 0; i < m; i++) mx = max(mx, matrix[i][j]);
            for (int i = 0; i < m; i++) if (matrix[i][j] == -1) matrix[i][j] = mx;
        }        
        return matrix;
    }
};
```

### 3034. 匹配模式数组的子数组数目 I

给你一个下标从 0 开始长度为 n 的整数数组 nums ，和一个下标从 0 开始长度为 m 的整数数组 pattern ，pattern 数组只包含整数 -1 ，0 和 1 。

大小为 m + 1 的子数组 nums[i..j] 如果对于每个元素 pattern[k] 都满足以下条件，那么我们说这个子数组匹配模式数组 pattern ：

* 如果 pattern[k] == 1 ，那么 nums[i + k + 1] > nums[i + k]
* 如果 pattern[k] == 0 ，那么 nums[i + k + 1] == nums[i + k]
* 如果 pattern[k] == -1 ，那么 nums[i + k + 1] < nums[i + k]

请你返回匹配 pattern 的 nums 子数组的 数目 。

```cpp
// Same as #3036
```

### 3035. 回文字符串的最大数量

给你一个下标从 0 开始的字符串数组 words ，数组的长度为 n ，且包含下标从 0 开始的若干字符串。

你可以执行以下操作 任意 次数（包括零次）：选择整数i、j、x和y，满足0 <= i, j < n，0 <= x < words[i].length，0 <= y < words[j].length，交换 字符 words[i][x] 和 words[j][y] 。

返回一个整数，表示在执行一些操作后，words 中可以包含的回文串的 最大 数量。

注意：在操作过程中，i 和 j 可以相等。

```cpp
class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        unordered_map<int, int> m;
        for (auto &w : words) for (auto &c : w) m[c]++;

        int tot = 0;
        for (auto &[k, v] : m) tot += (v & 1) ? v-1 : v;

        vector<int> lens;
        for (auto &w : words) lens.push_back(w.size());
        ranges::sort(lens);

        int ans = 0;
        for (auto &len : lens) {
            tot -= len / 2 * 2;
            if (tot < 0) break;
            ans++;
        }
        return ans;
    }
};
```

### 3036. 匹配模式数组的子数组数目 II

给你一个下标从 0 开始长度为 n 的整数数组 nums ，和一个下标从 0 开始长度为 m 的整数数组 pattern ，pattern 数组只包含整数 -1 ，0 和 1 。

大小为 m + 1 的子数组 nums[i..j] 如果对于每个元素 pattern[k] 都满足以下条件，那么我们说这个子数组匹配模式数组 pattern ：

* 如果 pattern[k] == 1 ，那么 nums[i + k + 1] > nums[i + k]
* 如果 pattern[k] == 0 ，那么 nums[i + k + 1] == nums[i + k]
* 如果 pattern[k] == -1 ，那么 nums[i + k + 1] < nums[i + k]

请你返回匹配 pattern 的 nums 子数组的 数目 。

```cpp
mt19937 gen(random_device{}());
int rnd(int x, int y) { return uniform_int_distribution<int>(x, y)(gen); }

int m1 = 998244353 + rnd(0, 1e9), b1 = 233 + rnd(0, 1e3);
int m2 = 998244353 + rnd(0, 1e9), b2 = 233 + rnd(0, 1e3);

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
    int n;
    SH1 h1, h2;

    SH2(string &s) : n(s.size()), h1(SH1(s, m1, b1)), h2(SH1(s, m2, b2)) {}

    long long hash() { return hash(0, n - 1); }

    long long hash(int l, int r) {  // [i, j], 0 based
        return h1.hash(l, r) * m1 + h2.hash(l, r);
    }
};

class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        string s;
        for (int i = 1; i < nums.size(); i++) s += 'g' + (nums[i] > nums[i-1] ? 1 : (nums[i] < nums[i-1] ? -1 : 0));
        string p;
        for (auto i : pattern) p += 'g' + i;

        int ans = 0;
        auto h = SH2(p).hash();
        long long hs = SH2(s);
        for (int i = 0, j = p.size()-1; j < s.size(); i++, j++) {
            ans += hs.hash(i, j) == h;
        }
        return ans;
    }
};
```

## 第 385 场周赛

### 3042. 统计前后缀下标对 I

给你一个下标从 0 开始的字符串数组 words 。

定义一个 布尔 函数 isPrefixAndSuffix ，它接受两个字符串参数 str1 和 str2 ：

当 str1 同时是 str2 的前缀（prefix）和后缀（suffix）时，isPrefixAndSuffix(str1, str2) 返回 true，否则返回 false。

例如，isPrefixAndSuffix("aba", "ababa") 返回 true，因为 "aba" 既是 "ababa" 的前缀，也是 "ababa" 的后缀，但是 isPrefixAndSuffix("abc", "abcd") 返回 false。

以整数形式，返回满足 i < j 且 isPrefixAndSuffix(words[i], words[j]) 为 true 的下标对 (i, j) 的 数量 。

```cpp
class Solution {
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        auto ok = [&](int i, int j) {
            auto &s1 = words[i];
            auto &s2 = words[j];
            if (s1.size() > s2.size()) return false;
            for (int k = 0; k < s1.size(); k++) if (s1[k] != s2[k]) return false;
            for (int k = 0; k < s1.size(); k++) if (s1[s1.size()-1-k] != s2[s2.size()-1-k]) return false;
            return true;
        };

        int ans = 0, n = words.size();
        for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) ans += ok(i, j);
        return ans;
    }
};
```

### 3043. 最长公共前缀的长度

给你两个 正整数 数组 arr1 和 arr2 。

正整数的 前缀 是其 最左边 的一位或多位数字组成的整数。例如，123 是整数 12345 的前缀，而 234 不是 。

设若整数 c 是整数 a 和 b 的 公共前缀 ，那么 c 需要同时是 a 和 b 的前缀。例如，5655359 和 56554 有公共前缀 565 ，而 1223 和 43456 没有 公共前缀。

你需要找出属于 arr1 的整数 x 和属于 arr2 的整数 y 组成的所有数对 (x, y) 之中最长的公共前缀的长度。

返回所有数对之中最长公共前缀的长度。如果它们之间不存在公共前缀，则返回 0 。

```cpp
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> s;
        for (auto i : arr1) {
            for (; i; i /= 10) s.insert(i);
        }

        int ans = 0;
        for (auto i : arr2) {
            for(; i; i /= 10) if (s.contains(i)) ans = max(ans, i);
        }        
        return ans ? to_string(ans).size() : 0;
    }
};
```
### 3044. 出现频率最高的质数

给你一个大小为 m x n 、下标从 0 开始的二维矩阵 mat 。在每个单元格，你可以按以下方式生成数字：

最多有 8 条路径可以选择：东，东南，南，西南，西，西北，北，东北。选择其中一条路径，沿着这个方向移动，并且将路径上的数字添加到正在形成的数字后面。

注意，每一步都会生成数字，例如，如果路径上的数字是 1, 9, 1，那么在这个方向上会生成三个数字：1, 19, 191 。

返回在遍历矩阵所创建的所有数字中，出现频率最高的、大于 10的 质数；如果不存在这样的质数，则返回 -1 。如果存在多个出现频率最高的质数，那么返回其中最大的那个。

注意：移动过程中不允许改变方向。

```cpp
static constexpr int dirs[8][2] = {1, -1, 1, 0, 1, 1, 0, 1, 0, -1, -1, 0, -1, -1, -1, 1};

class Solution {
public:
    bool isprime(int n) {
        for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
        return true;
    }

    int mostFrequentPrime(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        map<int, int> cnt;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (auto &[dx, dy] : dirs) {
                    int x = i + dx, y = j + dy, v = mat[i][j];
                    while (x >= 0 && x < m && y >= 0 && y < n) {
                        v = v * 10 + mat[x][y];
                        if (cnt.contains(v) || isprime(v)) cnt[v]++;
                        x += dx, y += dy;
                    }
                }
            }
        }
        int ans = -1, c = 0;
        for (auto &[k, v] : cnt) {
            if (ans == -1 || v > c || (v == c && k > ans)) ans = k, c = v;
        }
        return ans;
    }
};
```

### 3045. 统计前后缀下标对 II

给你一个下标从 0 开始的字符串数组 words 。

定义一个 布尔 函数 isPrefixAndSuffix ，它接受两个字符串参数 str1 和 str2 ：

当 str1 同时是 str2 的前缀（prefix）和后缀（suffix）时，isPrefixAndSuffix(str1, str2) 返回 true，否则返回 false。

例如，isPrefixAndSuffix("aba", "ababa") 返回 true，因为 "aba" 既是 "ababa" 的前缀，也是 "ababa" 的后缀，但是 isPrefixAndSuffix("abc", "abcd") 返回 false。

以整数形式，返回满足 i < j 且 isPrefixAndSuffix(words[i], words[j]) 为 true 的下标对 (i, j) 的 数量 。

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


int m1 = 998244353 + rnd(0, 1e9), b1 = 233 + rnd(0, 1e3);
int m2 = 998244353 + rnd(0, 1e9), b2 = 233 + rnd(0, 1e3);

struct SH2 {
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
    long long countPrefixSuffixPairs(vector<string>& words) {
        map<int, int> m;
        ll ans = 0;
        for (int i = 0; i < words.size(); i++) {
            auto s = words[i];
            auto hs = SH2(s);
            for (int j = 0; j < s.size(); j++) {
                auto h1 = hs.hash(0, j), h2 = hs.hash(s.size()-1-j, s.size()-1);
                if (h1 == h2) ans += m[h1];
            }
            m[hs.hash()]++;
        }
        return ans;
    }
};
```

## 第 386 场周赛

### 3046. 分割数组

给你一个长度为 偶数 的整数数组 nums 。你需要将这个数组分割成 nums1 和 nums2 两部分，要求：

* nums1.length == nums2.length == nums.length / 2 。
* nums1 应包含 互不相同 的元素。
* nums2也应包含 互不相同 的元素。
  
如果能够分割数组就返回 true ，否则返回 false 。

```cpp
class Solution {
public:
    bool isPossibleToSplit(vector<int>& nums) {
        map<int, int> m;
        for (auto i : nums) if (++m[i] > 2) return false;
        return true;
    }
};
```

### 3047. 求交集区域内的最大正方形面积

在二维平面上存在 n 个矩形。给你两个下标从 0 开始的二维整数数组 bottomLeft 和 topRight，两个数组的大小都是 n x 2 ，其中 bottomLeft[i] 和 topRight[i] 分别代表第 i 个矩形的 左下角 和 右上角 坐标。

我们定义 向右 的方向为 x 轴正半轴（x 坐标增加），向左 的方向为 x 轴负半轴（x 坐标减少）。同样地，定义 向上 的方向为 y 轴正半轴（y 坐标增加），向下 的方向为 y 轴负半轴（y 坐标减少）。

你可以选择一个区域，该区域由两个矩形的 交集 形成。你需要找出能够放入该区域 内 的 最大 正方形面积，并选择最优解。

返回能够放入交集区域的正方形的 最大 可能面积，如果矩形之间不存在任何交集区域，则返回 0。

```cpp
class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        long long ans = 0;
        for (int i = 0; i < bottomLeft.size(); i++) {
            auto &b1 = bottomLeft[i];
            auto &t1 = topRight[i];
            for (int j = i+1; j < bottomLeft.size(); j++) {
                auto &b2 = bottomLeft[j];
                auto &t2 = topRight[j];
                long long w = min(t1[0], t2[0]) - max(b1[0], b2[0]);
                long long h = min(t1[1], t2[1]) - max(b1[1], b2[1]);
                if(w > 0 && h > 0) ans = max(ans, min(w, h));
            }
        }
        return (long long)ans * ans;
    }
};
```

### 3048. 标记所有下标的最早秒数 I

给你两个下标从 1 开始的整数数组 nums 和 changeIndices ，数组的长度分别为 n 和 m 。

一开始，nums 中所有下标都是未标记的，你的任务是标记 nums 中 所有 下标。

从第 1 秒到第 m 秒（包括 第 m 秒），对于每一秒 s ，你可以执行以下操作 之一 ：

* 选择范围 [1, n] 中的一个下标 i ，并且将 nums[i] 减少 1 。
* 如果 nums[changeIndices[s]] 等于 0 ，标记 下标 changeIndices[s] 。
* 什么也不做。
  
请你返回范围 [1, m] 中的一个整数，表示最优操作下，标记 nums 中 所有 下标的 最早秒数 ，如果无法标记所有下标，返回 -1 。

```cpp
class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {        
        if (changeIndices.size() < nums.size()) return -1;
        for (auto &i : changeIndices) i--;

        auto ok = [&](int x) {
            unordered_map<int, int> last;
            for (int i = 0; i < x; i++) last[changeIndices[i]] = i;
            if (last.size() != nums.size()) return false;

            for (int i = 0, c = 0; i < x; i++) {
                if (i == last[changeIndices[i]]) {
                    c -= nums[changeIndices[i]];
                    if (c < 0) return false;
                } else {
                    c++;
                }
            }
            return true;
        };        

        int st = nums.size(), ed = changeIndices.size();
        while (st < ed) {
            int md = (st + ed) >> 1;
            if (ok(md)) ed = md;
            else st = md + 1;
        }
        return ok(st) ? st : -1;
    }
};
```

### 3049. 标记所有下标的最早秒数 II (TBD)

给你两个下标从 1 开始的整数数组 nums 和 changeIndices ，数组的长度分别为 n 和 m 。

一开始，nums 中所有下标都是未标记的，你的任务是标记 nums 中 所有 下标。

从第 1 秒到第 m 秒（包括 第 m 秒），对于每一秒 s ，你可以执行以下操作 之一 ：

* 选择范围 [1, n] 中的一个下标 i ，并且将 nums[i] 减少 1 。
* 将 nums[changeIndices[s]] 设置成任意的 非负 整数。
* 选择范围 [1, n] 中的一个下标 i ， 满足 nums[i] 等于 0, 并 标记 下标 i 。
* 什么也不做。

请你返回范围 [1, m] 中的一个整数，表示最优操作下，标记 nums 中 所有 下标的 最早秒数 ，如果无法标记所有下标，返回 -1 。

## 第 387 场周赛

### 3069. 将元素分配到两个数组中 I

给你一个下标从 1 开始、包含 不同 整数的数组 nums ，数组长度为 n 。

你需要通过 n 次操作，将 nums 中的所有元素分配到两个数组 arr1 和 arr2 中。在第一次操作中，将 nums[1] 追加到 arr1 。在第二次操作中，将 nums[2] 追加到 arr2 。之后，在第 i 次操作中：

如果 arr1 的最后一个元素 大于 arr2 的最后一个元素，就将 nums[i] 追加到 arr1 。否则，将 nums[i] 追加到 arr2 。

通过连接数组 arr1 和 arr2 形成数组 result 。例如，如果 arr1 == [1,2,3] 且 arr2 == [4,5,6] ，那么 result = [1,2,3,4,5,6] 。
返回数组 result 。

```cpp
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> a{nums[0]}, b{nums[1]};
        for (int i = 2; i < nums.size(); i++) {
            (a.back() > b.back() ? a : b).push_back(nums[i]);
        }
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};
```

### 3070. 元素和小于等于 k 的子矩阵的数目

给你一个下标从 0 开始的整数矩阵 grid 和一个整数 k。
返回包含 grid 左上角元素、元素和小于或等于 k 的 子矩阵 的数目。

```cpp
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int ans = 0, m = grid.size(), n = grid[0].size();
        vector<vector<int>> pre(m+1, vector<int>(n+1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pre[i+1][j+1] = grid[i][j] + pre[i+1][j] + pre[i][j+1] - pre[i][j];
                ans += pre[i+1][j+1] <= k;
            }   
        }
        return ans;
    }
};
```

### 3071. 在矩阵上写出字母 Y 所需的最少操作次数

给你一个下标从 0 开始、大小为 n x n 的矩阵 grid ，其中 n 为奇数，且 grid[r][c] 的值为 0 、1 或 2 。

如果一个单元格属于以下三条线中的任一一条，我们就认为它是字母 Y 的一部分：
从左上角单元格开始到矩阵中心单元格结束的对角线。
从右上角单元格开始到矩阵中心单元格结束的对角线。
从中心单元格开始到矩阵底部边界结束的垂直线。

当且仅当满足以下全部条件时，可以判定矩阵上写有字母 Y ：
属于 Y 的所有单元格的值相等。
不属于 Y 的所有单元格的值相等。
属于 Y 的单元格的值与不属于Y的单元格的值不同。

每次操作你可以将任意单元格的值改变为 0 、1 或 2 。返回在矩阵上写出字母 Y 所需的 最少 操作次数。

```cpp
class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        int n = grid.size(), m = n / 2;
        auto ok = [&](int x, int y) {
            if (x >= m) return y == m;
            if (y <= m) return x == y;
            return x + y == n-1;
        };

        auto f = [&](int n1, int n2) {
            int ans = 0;
            for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
                if (ok(i, j)) ans += grid[i][j] != n1;
                else ans += grid[i][j] != n2;
            }
            return ans;
        };

        int ans = INT_MAX;
        for (int i = 0; i <= 2; i++) for (int j = 0; j <= 2; j++) if (i != j) ans = min(ans, f(i, j));
        return ans;        
    }
};
```

### 3072. 将元素分配到两个数组中 II

给你一个下标从 1 开始、长度为 n 的整数数组 nums 。

现定义函数 greaterCount ，使得 greaterCount(arr, val) 返回数组 arr 中 严格大于 val 的元素数量。

你需要使用 n 次操作，将 nums 的所有元素分配到两个数组 arr1 和 arr2 中。在第一次操作中，将 nums[1] 追加到 arr1 。在第二次操作中，将 nums[2] 追加到 arr2 。之后，在第 i 次操作中：

如果 greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]) ，将 nums[i] 追加到 arr1 。
如果 greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]) ，将 nums[i] 追加到 arr2 。
如果 greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]) ，将 nums[i] 追加到元素数量较少的数组中。
如果仍然相等，那么将 nums[i] 追加到 arr1 。
连接数组 arr1 和 arr2 形成数组 result 。例如，如果 arr1 == [1,2,3] 且 arr2 == [4,5,6] ，那么 result = [1,2,3,4,5,6] 。

返回整数数组 result 。

```cpp
struct DC {
    int n;
    vector<int> v;
    unordered_map<int, int> m;

    DC(vector<int> v) : v(v) {
        ranges::sort(v);
        v.erase(unique(v.begin(), v.end()), v.end());
        n = v.size();
        for (int i = 0; i < n; i++) m[v[i]] = i + 1;
    }

    int map(int x) { return m[x]; }
    int rmap(int x) { return v[x-1]; }
};

struct BIT {
    int n; vector<int> c;    

    BIT(int n): n(n), c(n + 1) {}

    void update(int i, int val = 1) { while (i < c.size()) c[i] += val, i += i & -i ; }        
    int pre(int i) { int ans = 0; while (i) ans += c[i], i -= i & -i; return ans; };
    int query(int l, int r) { return pre(r) - pre(l - 1); }
    int suf(int i) { return query(i, n); };
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        DC dc(nums);
        int n = dc.n;
        BIT t1(n), t2(n);
        vector<int> v1, v2;
        v1.push_back(nums[0]), t1.update(dc.map(nums[0]));
        v2.push_back(nums[1]), t2.update(dc.map(nums[1]));

        for (int i = 2; i < nums.size(); i++) {
            int cur = dc.map(nums[i]);
            int c1 = t1.suf(cur+1), c2 = t2.suf(cur+1);
            if (c1 > c2 | (c1 == c2 && v1.size() <= v2.size())) {
                v1.push_back(nums[i]), t1.update(cur);                
            } else {
                v2.push_back(nums[i]), t2.update(cur);
            }
        }
        v1.insert(v1.end(), v2.begin(), v2.end());
        return v1;
    }
};
```

## 第 388 场周赛

### 3074. 重新分装苹果

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

### 3075. 幸福值最大化的选择方案

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

### 3076. 数组中的最短非公共子字符串

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

### 3077. K 个不相交子数组的最大能量值

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

## 第 389 场周赛

### 3083. 字符串及其反转中是否存在同一子字符串

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

### 3084. 统计以给定字符开头和结尾的子字符串总数

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

### 3085. 成为 K 特殊字符串需要删除的最少字符数

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

### 3086. 拾起 K 个 1 需要的最少行动次数

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

## 第 390 场周赛

### 3090. 每个字符最多出现两次的最长子字符串

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

### 3091. 执行操作使数据元素之和大于等于 K

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

### 3092. 最高频率的 ID

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

### 3093. 最长公共后缀查询

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

## 第 391 场周赛

### 100263. 哈沙德数

如果一个整数能够被其各个数位上的数字之和整除，则称之为 哈沙德数（Harshad number）。给你一个整数 x 。如果 x 是 哈沙德数 ，则返回 x 各个数位上的数字之和，否则，返回 -1 。

```cpp
class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x) {
        int s = 0;
        for (int t = x; t; t /= 10) s += t % 10;
        return x % s == 0 ? s : -1; 
    }
};
```

### 100235. 换水问题 II
        
给你两个整数 numBottles 和 numExchange 。

numBottles 代表你最初拥有的满水瓶数量。在一次操作中，你可以执行以下操作之一：

* 喝掉任意数量的满水瓶，使它们变成空水瓶。
* 用 numExchange 个空水瓶交换一个满水瓶。然后，将 numExchange 的值增加 1 。

注意，你不能使用相同的 numExchange 值交换多批空水瓶。例如，如果 numBottles == 3 并且 numExchange == 1 ，则不能用 3 个空水瓶交换成 3 个满水瓶。

返回你 最多 可以喝到多少瓶水。

```cpp
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int ans = numBottles;
        while (numBottles >= numExchange) {
            ans++, numBottles += 1 - numExchange++;
        }
        return ans;
    }
};
```

### 100266. 交替子数组计数

给你一个二进制数组nums 。

如果一个子数组中 不存在 两个 相邻 元素的值 相同 的情况，我们称这样的子数组为 交替子数组 。

返回数组 nums 中交替子数组的数量。

```cpp
class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        long long ans = 0, cur = 0;
        for (int i = 0; i < nums.size(); i++) {
            (i == 0 || nums[i] == nums[i-1]) ? cur = 1 : cur++;
            ans += cur;
        }
        return ans;
    }
};
```

### 100240. 最小化曼哈顿距离

给你一个下标从 0 开始的数组 points ，它表示二维平面上一些点的整数坐标，其中 points[i] = [xi, yi] 。

两点之间的距离定义为它们的曼哈顿距离。请你恰好移除一个点，返回移除后任意两点之间的 最大 距离可能的 最小 值。

```cpp
class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        // 点集的最大曼哈顿距离为把每个点的x-y排序后的最大值-最小值，和x+y排序后的最大值-最小值，中取最大值
        // ∣a−b∣ = max⁡(a−b, b−a)
        // |x0-x1| + |y0-y1| = max(
        //                       x0-x1+y0-y1 = (x0+y0) - (x1+y1)
        //                       x0-x1+y1-y0 = (x0-y1) - (x1-y1)
        //                       x1-x0+y0-y1 = (x1-y1) - (x0-y0)
        //                       x1-x0+y1-y0 = (x1+y1) - (x0+y0)
        //                     ）
        // 就是说x+y里的最大值-最小值 和 x-y里的最大值-最小值，再取最大值
        int ans = INT_MAX;
        multiset<int> s1, s2;
        for (auto &p : points) s1.insert(p[0]-p[1]), s2.insert(p[0]+p[1]);
        for (auto &p : points) {
            int t1 = p[0]-p[1], t2 = p[0]+p[1];
            s1.erase(s1.find(t1)), s2.erase(s2.find(t2));
            ans = min(ans, max(*s1.rbegin() - *s1.begin(), *s2.rbegin() - *s2.begin()));
            s1.insert(t1), s2.insert(t2);
        }
        return ans;
    }
};
```

## 第 392 场周赛

### 100264. 最长的严格递增或递减子数组

给你一个整数数组 nums 。返回数组 nums 中 严格递增 或 严格递减 的最长非空子数组的长度。

```cpp
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int ans = 1, dp1 = 1, dp2 = 1;
        for (int i = 1; i < nums.size(); i++) {
            dp1 = nums[i] > nums[i-1] ? dp1+1 : 1;
            dp2 = nums[i] < nums[i-1] ? dp2+1 : 1;
            ans = max(ans, max(dp1, dp2));
        }
        return ans;
    }
};
```

### 100242. 满足距离约束且字典序最小的字符串

给你一个字符串 s 和一个整数 k 。

定义函数 distance(s1, s2) ，用于衡量两个长度为 n 的字符串 s1 和 s2 之间的距离，即：

字符 'a' 到 'z' 按 循环 顺序排列，对于区间 [0, n - 1] 中的 i ，计算所有「 s1[i] 和 s2[i] 之间 最小距离」的 和 。
例如，distance("ab", "cd") == 4 ，且 distance("a", "z") == 1 。

你可以对字符串 s 执行 任意次 操作。在每次操作中，可以将 s 中的一个字母 改变 为 任意 其他小写英文字母。

返回一个字符串，表示在执行一些操作后你可以得到的 字典序最小 的字符串 t ，且满足 distance(s, t) <= k 。

```cpp
class Solution {
public:
    string getSmallestString(string s, int k) {
        for (int i = 0; i < s.size(); i++) {
            int dis = min(s[i] - 'a', 'a' + 26 - s[i]);
            if (dis <= k) k -= dis, s[i] = 'a';
            else {
                s[i] -= k; break;
            }
        }
        return s;
    }
};
```

### 3107. 使数组中位数等于 K 的最少操作数

给你一个整数数组 nums 和一个 非负 整数 k 。

一次操作中，你可以选择任一下标 i ，然后将 nums[i] 加 1 或者减 1 。

请你返回将 nums 中位数 变为 k 所需要的 最少 操作次数。

一个数组的 中位数 指的是数组按 非递减 顺序排序后最中间的元素。如果数组长度为偶数，我们选择中间两个数的较大值为中位数。

```cpp
class Solution {
public:
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        int n = nums.size(), m = n / 2;
        ranges::nth_element(nums, nums.begin() + m);        
        long long ans = 0;
        if (nums[m] > k) {
            for (int i = 0; i <= m; i++) ans += max(nums[i] - k,  0);
        } else {
            for (int i = m; i < n; i++) ans += max(k - nums[i], 0);
        }
        return ans;        
    }
};
```

### 100244. 带权图里旅途的最小代价

给你一个 n 个节点的带权无向图，节点编号为 0 到 n - 1 。

给你一个整数 n 和一个数组 edges ，其中 edges[i] = [ui, vi, wi] 表示节点 ui 和 vi 之间有一条权值为 wi 的无向边。

在图中，一趟旅途包含一系列节点和边。旅途开始和结束点都是图中的节点，且图中存在连接旅途中相邻节点的边。注意，一趟旅途可能访问同一条边或者同一个节点多次。

如果旅途开始于节点 u ，结束于节点 v ，我们定义这一趟旅途的 代价 是经过的边权按位与 AND 的结果。换句话说，如果经过的边对应的边权为 w0, w1, w2, ..., wk ，那么代价为w0 & w1 & w2 & ... & wk ，其中 & 表示按位与 AND 操作。

给你一个二维数组 query ，其中 query[i] = [si, ti] 。对于每一个查询，你需要找出从节点开始 si ，在节点 ti 处结束的旅途的最小代价。如果不存在这样的旅途，答案为 -1 。

返回数组 answer ，其中 answer[i] 表示对于查询 i 的 最小 旅途代价。

```cpp
struct DisjointSet {
    vector<int> pa, size;
    DisjointSet(int n): pa(n), size(n, 1) { for (int i = 0; i < n; i++) pa[i] = i; }
    int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        pa[y] = x; size[x] += size[y];
    }
};

class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        DisjointSet ds(n);
        for (auto &e : edges) ds.merge(e[0], e[1]);

        map<int, int> m;
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2], fa = ds.find(u);
            if (m.contains(fa)) m[fa] &= w;
            else m[fa] = w;
        }        

        vector<int> ans(query.size(), -1);
        for (int i = 0; i < query.size(); i++) {
            int u = query[i][0], v = query[i][1];
            if (u == v) ans[i] = 0;
            else if (ds.find(u) == ds.find(v)) ans[i] = m[ds.find(u)];
        }
        return ans;
    }
};
```

## 第 393 场周赛

### 3114. 替换字符可以得到的最晚时间

给你一个字符串 s，表示一个 12 小时制的时间格式，其中一些数字（可能没有）被 "?" 替换。

12 小时制时间格式为 "HH:MM" ，其中 HH 的取值范围为 00 至 11，MM 的取值范围为 00 至 59。最早的时间为 00:00，最晚的时间为 11:59。

你需要将 s 中的 所有 "?" 字符替换为数字，使得结果字符串代表的时间是一个 有效 的 12 小时制时间，并且是可能的 最晚 时间。

返回结果字符串。

```cpp
class Solution {
public:
    string findLatestTime(string s) {
        auto ok = [&](int t, string s) {
            return (s[0] == '?' || s[0]-'0' == t / 10) &&
                   (s[1] == '?' || s[1]-'0' == t % 10);
        };

        int h, m;
        for (h = 11; h >= 0; h--) if (ok(h, s.substr(0, 2))) break;
        for (m = 59; m >= 0; m--) if (ok(m, s.substr(3, 2))) break;

        char ans[6];
        sprintf(ans, "%02d:%02d", h, m);
        return string(ans);
    }
};
```

### 3115. 质数的最大距离

给你一个整数数组 nums。

返回两个（不一定不同的）质数在 nums 中 下标 的 最大距离。

```cpp
class Solution {
public:    
    bool isprime(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

    int maximumPrimeDifference(vector<int>& nums) {
        vector<int> ids;
        for(int i = 0; i < nums.size(); i++) if (isprime(nums[i])) ids.push_back(i);
        return ranges::max(ids) - ranges::min(ids);
    }
};
```

### 3116. 单面值组合的第 K 小金额

给你一个整数数组 coins 表示不同面额的硬币，另给你一个整数 k 。

你有无限量的每种面额的硬币。但是，你 不能 组合使用不同面额的硬币。

返回使用这些硬币能制造的 第 kth 小 金额。

```cpp
class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        auto ok = [&](long long x) {      
            long long cnt = 0;      
            for (int i = 1; i < 1 << n; i++) { // 容斥原理，选奇数个数时符号位+，否则为-
                long long lcm_res = 1;
                for (int j = 0; j < n; j++) if (i >> j & 1) lcm_res = lcm(lcm_res, coins[j]);
                long long sign = __builtin_popcount(i) & 1 ? 1 : -1;
                cnt += x / lcm_res * sign;
            }
            return cnt >= k;
        };
        long long st = k, ed = (long long)ranges::min(coins) * k;
        while (st < ed) {
            auto md = (st + ed) >> 1;
            if (ok(md)) ed = md;
            else st = md + 1;
        }
        return st;
    }
};
```

### 3117. 划分数组得到最小的值之和

给你两个数组 nums 和 andValues，长度分别为 n 和 m。

数组的 值 等于该数组的 最后一个 元素。

你需要将 nums 划分为 m 个 不相交的连续 子数组，对于第 ith 个子数组 [li, ri]，子数组元素的按位AND运算结果等于 andValues[i]，换句话说，对所有的 1 <= i <= m，nums[li] & nums[li + 1] & ... & nums[ri] == andValues[i] ，其中 & 表示按位AND运算符。

返回将 nums 划分为 m 个子数组所能得到的可能的 最小 子数组 值 之和。如果无法完成这样的划分，则返回 -1 。

```cpp
class Solution {
public:
    int inf, n, m;
    unordered_map<long long, int> mm;
    
    // 两个剪枝不要也能过
    int dfs (int i, int j, int sum, vector<int>& nums, vector<int>& andValues){
        if (n - i < m - j) return inf; // 剩下的数字不够了
        if (i == n && j == m) return 0;
        if (i == n || j == m) return inf;            

        sum &= nums[i];
        if (sum < andValues[j]) return inf; // 与更多的数字只会越来越小

        long long key = (long long) i << 36 | (long long) j << 32 | sum;
        if (mm.contains(key))return mm[key];
                    
        int ans = dfs(i+1, j, sum, nums, andValues);
        if (sum == andValues[j]) ans = min(ans, dfs(i+1, j+1, -1, nums, andValues) + nums[i]);
        return mm[key] = ans;
    }

    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        n = nums.size(), m = andValues.size(), inf = INT_MAX >> 1;        
        // dfs使用function<int(int, int, int)>会超时
        auto ans = dfs(0, 0, -1, nums, andValues);
        return ans == inf ? -1 : ans;
    }
};
```

## 第 394 场周赛

### 3120. 统计特殊字母的数量 I

给你一个字符串 word。如果 word 中同时存在某个字母的小写形式和大写形式，则称这个字母为 特殊字母 。

返回 word 中 特殊字母 的数量。

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {
        int ans = 0;
        for (int i = 0; i < 26; i++) ans += word.find('a'+i) != -1 && word.find('A'+i) != -1;
        return ans;        
    }
};
```

### 3121. 统计特殊字母的数量 II

给你一个字符串 word。如果 word 中同时出现某个字母 c 的小写形式和大写形式，并且 每个 小写形式的 c 都出现在第一个大写形式的 c 之前，则称字母 c 是一个 特殊字母 。

返回 word 中 特殊字母 的数量。

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {
        int ans = 0;
        for (int i = 0; i < 26; i++) {            
            int id1 = word.find_last_of('a'+i);
			int id2 = word.find_first_of('A'+i);
			ans += id1 != -1 && id2 != -1 && id1 < id2;
        }
        return ans;        
    }
};
```

### 3122. 使矩阵满足条件的最少操作次数

给你一个大小为 m x n 的二维矩形 grid 。每次 操作 中，你可以将 任一 格子的值修改为 任意 非负整数。完成所有操作后，你需要确保每个格子 grid[i][j] 的值满足：

* 如果下面相邻格子存在的话，它们的值相等，也就是 grid[i][j] == grid[i + 1][j]（如果存在）。
* 如果右边相邻格子存在的话，它们的值不相等，也就是 grid[i][j] != grid[i][j + 1]（如果存在）。
  
请你返回需要的 最少 操作数目。

```cpp
class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(n+1, vector<int>(10));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 9; j++) {
                int mn = INT_MAX;
                for (int k = 0; k <= 9; k++) if (k != j) mn = min(mn, dp[i][k]);                

                dp[i+1][j] = mn;
                for (int k = 0; k < m; k++) dp[i+1][j] += grid[k][i] != j;
            }
        }
        return ranges::min(dp[n]);
    }
};
```

### 3123. 最短路径中的边

给你一个 n 个节点的无向带权图，节点编号为 0 到 n - 1 。图中总共有 m 条边，用二维数组 edges 表示，其中 edges[i] = [ai, bi, wi] 表示节点 ai 和 bi 之间有一条边权为 wi 的边。

对于节点 0 为出发点，节点 n - 1 为结束点的所有最短路，你需要返回一个长度为 m 的 boolean 数组 answer ，如果 edges[i] 至少 在其中一条最短路上，那么 answer[i] 为 true ，否则 answer[i] 为 false 。

请你返回数组 answer 。

注意，图可能不连通。

```cpp
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        vector<vector<tii>> g(n);
        for (int i = 0; i < edges.size(); i++) {
            auto &e = edges[i];
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w, i);
            g[v].emplace_back(u, w, i);
        }

        vector<int> dis(n, INT_MAX);        
        priority_queue<pii, vector<pii>, greater<>> q;
        dis[0] = 0, q.emplace(0, 0);
        while (!q.empty()) {
            auto [d, x] = q.top(); q.pop();
            if (d > dis[x]) continue;
            for (auto [y, w, _] : g[x]) {
                int nd = d + w;
                if (nd < dis[y]) dis[y] = nd, q.emplace(nd, y);
            }
        }

        vector<bool> ans(edges.size());
        if (dis[n-1] == INT_MAX) return ans;

        vector<bool> vs(n);
        function<void(int)> dfs = [&](int x) {
            vs[x] = true;
            for (auto [y, w, i] : g[x]) {
                if (dis[y] + w == dis[x]) {
                    ans[i] = true;
                    if (!vs[y]) dfs(y);
                }
            }
        };
        dfs(n-1);
        return ans;
    }
};
```

## 第 395 场周赛

### 3131. 找出与数组相加的整数 I

给你两个长度相等的数组 nums1 和 nums2。

数组 nums1 中的每个元素都与变量 x 所表示的整数相加。如果 x 为负数，则表现为元素值的减少。

在与 x 相加后，nums1 和 nums2 相等 。当两个数组中包含相同的整数，并且这些整数出现的频次相同时，两个数组 相等 。

返回整数 x 。

```cpp
class Solution {
public:
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {
        return ranges::min(nums2) - ranges::min(nums1);
    }
};
```

### 3132. 找出与数组相加的整数 II

给你两个整数数组 nums1 和 nums2。

从 nums1 中移除两个元素，并且所有其他元素都与变量 x 所表示的整数相加。如果 x 为负数，则表现为元素值的减少。

执行上述操作后，nums1 和 nums2 相等 。当两个数组中包含相同的整数，并且这些整数出现的频次相同时，两个数组 相等 。

返回能够实现数组相等的 最小 整数 x 。

```cpp
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        ranges::sort(nums1);
        ranges::sort(nums2);
        for (int i = 2; i >= 0; i--) {
            int d = nums2[0] - nums1[i];
            for (int j = i, k = 0; j < nums1.size(); j++) {
                if (nums1[j] + d == nums2[k] && ++k == nums2.size()) return d;
            }
        }
        return -1;
    }
};
```

### 3133. 数组最后一个元素的最小值

给你两个整数 n 和 x 。你需要构造一个长度为 n 的 正整数 数组 nums ，对于所有 0 <= i < n - 1 ，满足 nums[i + 1] 大于 nums[i] ，并且数组 nums 中所有元素的按位 AND 运算结果为 x 。

返回 nums[n - 1] 可能的 最小 值。

```cpp
class Solution {
public:
    long long minEnd(int n, int x) {
        n--;
        long long ans = x, a = x; // 把x转为long long，不然移位可能溢出
        for (int i = 0; n; n >>= 1) {
            while (a >> i & 1) i++;
            if (n & 1) ans |= 1LL << i; // 必须1LL，不然移位会溢出
            i++;
        }
        return ans;
    }
};
```

### 3134. 找出唯一性数组的中位数

给你一个整数数组 nums 。数组 nums 的 唯一性数组 是一个按元素从小到大排序的数组，包含了 nums 的所有
非空子数组中
不同元素的个数。

换句话说，这是由所有 0 <= i <= j < nums.length 的 distinct(nums[i..j]) 组成的递增数组。

其中，distinct(nums[i..j]) 表示从下标 i 到下标 j 的子数组中不同元素的数量。

返回 nums 唯一性数组 的 中位数 。

注意，数组的 中位数 定义为有序数组的中间元素。如果有两个中间元素，则取值较小的那个。

```cpp
// 二分找第k小/大的数（包括中位数）
// 小 ...... k ...... 大
//              x (考虑比<=x的数的个数，考虑这个数>=k的结论)
// 0 ......0 1 1 .... 1
// 满足二分要求
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long t = ((long long)n * (n + 1) / 2 + 1) / 2; // 二分找中位数
        auto ok = [&](int x) {            
            long long cnt = 0;
            unordered_map<int, int> m;            
            for (int i = 0, j = 0; j < n; j++) {
                m[nums[j]]++;
                while (m.size() > x) {
                    int tem = nums[i];
                    m[tem]--, i++;
                    if (m[tem] == 0) m.erase(tem);
                }
                cnt += j - i + 1;
                if (cnt >= t) return true;
            }
            return cnt >= t;
        };

        int st = 1, ed = n;
        while (st < ed) {
            int md = (st + ed) >> 1;
            if (ok(md)) ed = md;
            else st = md + 1;
        }            
        return st;
    }
};
```





## 第 396 场周赛

### 3136. 有效单词

有效单词 需要满足以下几个条件：

* 至少 包含 3 个字符。
* 由数字 0-9 和英文大小写字母组成。（不必包含所有这类字符。）
* 至少 包含一个 元音字母 。
* 至少 包含一个 辅音字母 。
* 给你一个字符串 word 。如果 word 是一个有效单词，则返回 true ，否则返回 false 。

注意： 'a'、'e'、'i'、'o'、'u' 及其大写形式都属于 元音字母 。英文中的 辅音字母 是指那些除元音字母之外的字母。


```cpp
class Solution {
public:
    bool isValid(string word) {
        auto ok = [&](char x) {
            x = tolower(x);
            return x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u';
        };

        if (word.size() < 3) return false;
        for (auto i : word) if (!isalnum(i)) return false;
        bool has1 = false, has2 = false;
        for (auto i : word) if (isalpha(i)) has1 |= ok(i), has2 |= !ok(i);
        return has1 && has2;
    }
};
```

### 3137. K 周期字符串需要的最少操作次数

给你一个长度为 n 的字符串 word 和一个整数 k ，其中 k 是 n 的因数。

在一次操作中，你可以选择任意两个下标 i 和 j，其中 0 <= i, j < n ，且这两个下标都可以被 k 整除，然后用从 j 开始的长度为 k 的子串替换从 i 开始的长度为 k 的子串。也就是说，将子串 word[i..i + k - 1] 替换为子串 word[j..j + k - 1] 。

返回使 word 成为 K 周期字符串 所需的 最少 操作次数。

如果存在某个长度为 k 的字符串 s，使得 word 可以表示为任意次数连接 s ，则称字符串 word 是 K 周期字符串 。例如，如果 word == "ababab"，那么 word 就是 s = "ab" 时的 2 周期字符串 。

```cpp
class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        map<string, int> m;
        for (int i = 0; i < word.size(); i += k) m[word.substr(i, k)]++;
        int ans = INT_MAX;
        for (auto &[_, v] : m) ans = min(ans, (int)word.size() / k - v);
        return ans;
    }
};
```

### 3138. 同位字符串连接的最小长度

给你一个字符串 s ，它由某个字符串 t 和若干 t  的 同位字符串 连接而成。

请你返回字符串 t 的 最小 可能长度。

同位字符串 指的是重新排列一个单词得到的另外一个字符串，原来字符串中的每个字符在新字符串中都恰好只使用一次。

```cpp
class Solution {
public:
    int minAnagramLength(string s) {
        int n = s.size();
        for (int i = 1; i <= n / 2; i++) {
            if (n % i != 0) continue;
            string t = s.substr(0, i); ranges::sort(t);
            bool ok = true;
            for (int j = i; j < n; j += i) {
                string t1 = s.substr(j, i); ranges::sort(t1);
                if (t != t1) { ok = false; break; }
            }
            if (ok) return i;
        }
        return n;
    }
};
```

### 3139. 使数组中所有元素相等的最小开销

给你一个整数数组 nums 和两个整数 cost1 和 cost2 。你可以执行以下 任一 操作 任意 次：

从 nums 中选择下标 i 并且将 nums[i] 增加 1 ，开销为 cost1。
选择 nums 中两个 不同 下标 i 和 j ，并且将 nums[i] 和 nums[j] 都 增加 1 ，开销为 cost2 。
你的目标是使数组中所有元素都 相等 ，请你返回需要的 最小开销 之和。

由于答案可能会很大，请你将它对 109 + 7 取余 后返回。

首先处理特殊情况，对于普通情况，假设目标位某个高度mx，问题等价于有n堆石头，每堆有mx-ai个石头，每次选一堆拿走一个，或者选两堆各拿走一个，求最小代价。

假设石头总数为s，最大一堆数量为m，剩余数量rest=s-m。

* 若rest <= m，则只能把rest全用操作2，剩下的用操作1。
* 否则，可以尽量全部使用操作2，最后剩余单个石头的话，用操作1。

目标高度至少为最大元素mx，但可能会更大，考虑枚举这个范围内的每个数值。枚举的上界如何确定？当处于第1种情况时，差值为m-rest，每次增加1个目标高度，差值可以减少n-2，则至多大约添加 m-rest / n-2 可以转为第2种情况，实际操作时需要多枚举2次，保证处理到所有可能的情况。处于第2种情况时，代价和总和挂钩，高度越高代价越大，除非通过增加高度把唯一一次cost1给去掉了，大概枚举个2、3次意思意思就可以了。

```cpp
static const int mod = 1e9 + 7;
class Solution {
public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        int n = nums.size();
        if (n == 1) return 0;
        if (n == 2) return (long long)(abs(nums[0] - nums[1])) * cost1 % mod;

        long long mx = ranges::max(nums);
        if (2 * cost1 <= cost2) {        
            long long ans = 0;    
            for (auto i : nums) ans += (long long)(mx - i) * cost1;
            return ans % mod;
        }        

        for (auto &i : nums) i = mx - i;
        long long s = accumulate(nums.begin(), nums.end(), 0LL);
        long long m = ranges::max(nums);

        long long ans = LLONG_MAX;
        long long d = (m - (s - m)) / (n - 2) + 2;
        for (int i = 0; i <= max(d, 2LL); i++) {
            long long m0 = m + i, s0 = s + (long long)n * i, ans0;
            if (s0 - m0 >= m0) {
                ans0 = s0 / 2 * cost2 + (s0 % 2) * cost1;
            } else {
                ans0 = (s0 - m0) * cost2 + (m0 - (s0 - m0)) * cost1;
            }
            ans = min(ans, ans0);
        }
        return ans % mod;
    }
};
```

## 第 397 场周赛

### 3146. 两个字符串的排列差

给你两个字符串 s 和 t，每个字符串中的字符都不重复，且 t 是 s 的一个排列。

排列差 定义为 s 和 t 中每个字符在两个字符串中位置的绝对差值之和。

返回 s 和 t 之间的 排列差 。

```cpp
class Solution {
public:
    int findPermutationDifference(string s, string t) {
        vector<int> m1(26), m2(26);
        for (int i = 0; i < s.size(); i++) m1[s[i]-'a'] = i, m2[t[i]-'a'] = i;
        int ans = 0;
        for (int i = 0; i < 26; i++) ans += abs(m1[i] - m2[i]);
        return ans;
    }
};
```

### 3147. 从魔法师身上吸取的最大能量

在神秘的地牢中，n 个魔法师站成一排。每个魔法师都拥有一个属性，这个属性可以给你提供能量。有些魔法师可能会给你负能量，即从你身上吸取能量。

你被施加了一种诅咒，当你从魔法师 i 处吸收能量后，你将被立即传送到魔法师 (i + k) 处。这一过程将重复进行，直到你到达一个不存在 (i + k) 的魔法师为止。

换句话说，你将选择一个起点，然后以 k 为间隔跳跃，直到到达魔法师序列的末端，在过程中吸收所有的能量。

给定一个数组 energy 和一个整数k，返回你能获得的 最大 能量。

```cpp
class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        for (int i = energy.size()-k-1; i >= 0; i--) energy[i] += energy[i+k];
        return ranges::max(energy);
    }
};
```

### 3148. 矩阵中的最大得分

给你一个由 正整数 组成、大小为 m x n 的矩阵 grid。你可以从矩阵中的任一单元格移动到另一个位于正下方或正右侧的任意单元格（不必相邻）。从值为 c1 的单元格移动到值为 c2 的单元格的得分为 c2 - c1 。

你可以从 任一 单元格开始，并且必须至少移动一次。

返回你能得到的 最大 总得分。

```cpp
class Solution {
public:
    int maxScore(vector<vector<int>>& a) {
        int m = a.size(), n = a[0].size(), ans = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;
                int mn = INT_MAX;
                if (i-1 >= 0) mn = min(mn, a[i-1][j]);
                if (j-1 >= 0) mn = min(mn, a[i][j-1]);
                ans = max(ans, a[i][j] - mn);
                a[i][j] = min(a[i][j], mn);
            }
        }
        return ans;
    }
};
```

### 3149. 找出分数最低的排列

给你一个数组 nums ，它是 [0, 1, 2, ..., n - 1] 的一个排列 。对于任意一个 [0, 1, 2, ..., n - 1] 的排列 perm ，其 分数 定义为：

score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|

返回具有 最低 分数的排列 perm 。如果存在多个满足题意且分数相等的排列，则返回其中字典序最小的一个。

状态压缩DP。首先观察定义，分数只跟每个数字以及其相邻数字有关系，跟具体位置无关，意味着循环以为数组不影响其分数，为保证分数最小，第一位必须为0，然后递归枚举下一位数字。考虑到中间会出现重复子问题，使用状态压缩DP。

dp[i][j] 表示已经选过的数字集合为i，并且前一位选择的数字为j时的最小值，dp[i][j] = dp[i | (1 << k)][k] 的最小值，使用pre记录取得最小值时选择的k，之后回溯构造答案。

```cpp
class Solution {
public:
    vector<int> findPermutation(vector<int>& a) {
        int n = a.size();
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        vector<vector<int>> pre(1 << n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) dp[(1 << n) - 1][i] = abs(i - a[0]);
        for (int i = (1 << n) - 1 - 2; i >= 0; i -= 2) { // 数字0是第一个选择的数字，因此状态里第0位必须为1
            for (int j = 0; j < n; j++) {
                if ((i >> j & 1) == 0) continue; // j必须在集合i中，因为j时前一次选择的数字，必须在已选择数字集合里
                for (int k = 0; k < n; k++) {
                    if (i >> k & 1) continue; // 下一个选择的数字必须不能出现在已选择数字的集合中
                    int t = dp[i | (1 << k)][k] + abs(j - a[k]);
                    if (t < dp[i][j]) dp[i][j] = t, pre[i][j] = k;
                }
            }
        }
        vector<int> ans;
        int i = 1, j = 0;
        while (true) {
            ans.push_back(j);
            if ((j = pre[i][j]) == -1) break; // 回溯直到没有前驱节点为止
            i |= 1 << j;
        }
        return ans;
    }
};
```

## 第 398 场周赛

### 3151. 特殊数组 I

如果数组的每一对相邻元素都是两个奇偶性不同的数字，则该数组被认为是一个 特殊数组 。

Aging 有一个整数数组 nums。如果 nums 是一个 特殊数组 ，返回 true，否则返回 false。

```cpp
class Solution {
public:
    bool isArraySpecial(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) if ((nums[i]&1) == (nums[i-1]&1)) return false;
        return true;
    }
};
```

### 3152. 特殊数组 II

如果数组的每一对相邻元素都是两个奇偶性不同的数字，则该数组被认为是一个 特殊数组 。

周洋哥有一个整数数组 nums 和一个二维整数矩阵 queries，对于 queries[i] = [fromi, toi]，请你帮助周洋哥检查子数组 nums[fromi..toi] 是不是一个 特殊数组 。

返回布尔数组 answer，如果 nums[fromi..toi] 是特殊数组，则 answer[i] 为 true ，否则，answer[i] 为 false 。

```cpp
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> v(n);
        for (int i = 1; i < n; i++) v[i] = v[i-1] + ((nums[i]&1) == (nums[i-1]&1));        
        vector<bool> ans;
        for (auto &q : queries) {
            int from = q[0], to = q[1];
            ans.push_back(v[to] - v[from] == 0);
        }
        return ans;
    }
};
```

### 3153. 所有数对中数位不同之和

有一个数组 nums ，它只包含 正 整数，所有正整数的数位长度都 相同 。

两个整数的 数位不同 指的是两个整数 相同 位置上不同数字的数目。

请返回 nums 中 所有 整数对里，数位不同之和。

```cpp
class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        long long ans = 0, n = nums.size();
        while(nums[0]) {
            vector<long long> cnt(10);
            for (auto &j : nums) cnt[j % 10]++, j /= 10;            
            for (auto &j : cnt) ans += j * (n - j);
        }
        return ans >> 1;
    }
};
```

### 3154. 到达第 K 级台阶的方案数

给你有一个 非负 整数 k 。有一个无限长度的台阶，最低 一层编号为 0 。

虎老师有一个整数 jump ，一开始值为 0 。虎老师从台阶 1 开始，虎老师可以使用 任意 次操作，目标是到达第 k 级台阶。假设虎老师位于台阶 i ，一次 操作 中，虎老师可以：

向下走一级到 i - 1 ，但该操作 不能 连续使用，如果在台阶第 0 级也不能使用。
向上走到台阶 i + 2jump 处，然后 jump 变为 jump + 1 。
请你返回虎老师到达台阶 k 处的总方案数。

注意 ，虎老师可能到达台阶 k 处后，通过一些操作重新回到台阶 k 处，这视为不同的方案。

```cpp
class Solution {
public:
    int waysToReachStair(int k) {        
        long long c[31][31];
        c[0][0] = 1;
        for (int i = 1; i <= 30; i++) {
            c[i][0] = 1;
            for (int j = 1; j <= 30; j++) c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
        int ans = 0;
        for (int i = 0; i <= 30; i++) {
            for (int j = 0; j <= i+1; j++) {
                if ((1LL << i) - j == k) ans += c[i+1][j];
            }
        }
        return ans;
    }
};
```

## 第 399 场周赛

### 100323. 优质数对的总数 I

给你两个整数数组 nums1 和 nums2，长度分别为 n 和 m。同时给你一个正整数 k。

如果 nums1[i] 可以被 nums2[j] * k 整除，则称数对 (i, j) 为 优质数对（0 <= i <= n - 1, 0 <= j <= m - 1）。

返回 优质数对 的总数。

```cpp
// 同100321
```

### 100326. 压缩字符串 III

给你一个字符串 word，请你使用以下算法进行压缩：

从空字符串 comp 开始。当 word 不为空 时，执行以下操作：

* 移除 word 的最长单字符前缀，该前缀由单一字符 c 重复多次组成，且该前缀长度 最多 为 9 。
* 将前缀的长度和字符 c 追加到 comp 。

返回字符串 comp 。

```cpp
class Solution {
public:
    string compressedString(string word) {
        string ans;
        char c;
        for (int i = 0, cnt = 0; i < word.size(); i++) {
            if (cnt == 0) c = word[i], cnt = 1;
            else if (c == word[i]) {
                if (++cnt == 9) {
                    ans += '9', ans += c; cnt = 0;
                }
            } else {
                ans += to_string(cnt) + c, c = word[i], cnt = 1;
            }
            if (i == word.size()-1 && cnt > 0) ans += to_string(cnt) + c;
        }
        return ans;
    }
};
```

### 100321. 优质数对的总数 II

给你两个整数数组 nums1 和 nums2，长度分别为 n 和 m。同时给你一个正整数 k。

如果 nums1[i] 可以被 nums2[j] * k 整除，则称数对 (i, j) 为 优质数对（0 <= i <= n - 1, 0 <= j <= m - 1）。

返回 优质数对 的总数。

```cpp
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<long long, long long> m;
        for (auto i : nums2) m[(long long) i * k]++;
        long long ans = 0;
        for (auto i : nums1) {
            for (long long j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    ans += m[j];
                    if (j != i / j) ans += m[i/j];
                }
            }
        }
        return ans;
    }
};
```

### 100306. 不包含相邻元素的子序列的最大和

给你一个整数数组 nums 和一个二维数组 queries，其中 queries[i] = [posi, xi]。

对于每个查询 i，首先将 nums[posi] 设置为 xi，然后计算查询 i 的答案，该答案为 nums 中 不包含相邻元素 的子序列的 最大 和。

返回所有查询的答案之和。

由于最终答案可能非常大，返回其对 109 + 7 取余 的结果。

子序列 是指从另一个数组中删除一些或不删除元素而不改变剩余元素顺序得到的数组。

```cpp
using ll = long long;
static const int mod = 1e9 + 7;

struct SegTreeNode { ll v00, v01, v10, v11; };
struct SegTree {
    ll n;
    vector<SegTreeNode> a;

    SegTree(ll n) : n(n), a(vector<SegTreeNode>(n * 4)) {};

    void update(ll id, ll d) {
        update(1, 1, n, id, id, d);
    }
    void update(ll k, ll l, ll r, ll L, ll R, ll d) {
        if (l == r) {
            a[k].v00 = a[k].v01 = a[k].v10 = 0, a[k].v11 = d;
            return;
        }
        int lc = k << 1, rc = lc | 1, md = (l + r) >> 1;
        if (md >= L) update(lc, l, md, L, R, d);
        if (md+1 <= R) update(rc, md+1, r, L, R, d);
        a[k].v00 = ranges::max({a[lc].v00+a[rc].v00, a[lc].v00+a[rc].v10, a[lc].v01+a[rc].v00});
        a[k].v01 = ranges::max({a[lc].v00+a[rc].v01, a[lc].v00+a[rc].v11, a[lc].v01+a[rc].v01});
        a[k].v10 = ranges::max({a[lc].v10+a[rc].v00, a[lc].v10+a[rc].v10, a[lc].v11+a[rc].v00});
        a[k].v11 = ranges::max({a[lc].v10+a[rc].v01, a[lc].v10+a[rc].v11, a[lc].v11+a[rc].v01});
    }
    ll query() {
        return ranges::max({a[1].v00, a[1].v01, a[1].v10, a[1].v11});
    }
};

class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        SegTree tr(n);
        for (int i = 0; i < n; i++) tr.update(i+1, nums[i]);
        long long ans = 0;
        for (auto q : queries) {
            int pos = q[0] + 1, x = q[1];
            tr.update(pos, x);
            ans += tr.query();
        }
        return ans % mod;
    }
};
```

## 第 400 场周赛

### 3168. 候诊室中的最少椅子数

给你一个字符串 s，模拟每秒钟的事件 i：

如果 s[i] == 'E'，表示有一位顾客进入候诊室并占用一把椅子。

如果 s[i] == 'L'，表示有一位顾客离开候诊室，从而释放一把椅子。

返回保证每位进入候诊室的顾客都能有椅子坐的 最少 椅子数，假设候诊室最初是 空的 。

```cpp
class Solution {
public:
    int minimumChairs(string s) {
        int ans = 0, cur = 0;
        for (auto i : s) cur += i == 'E' ? 1 : -1, ans = max(ans, cur);
        return ans;
    }
};
```

### 3169. 无需开会的工作日

给你一个正整数 days，表示员工可工作的总天数（从第 1 天开始）。另给你一个二维数组 meetings，长度为 n，其中 meetings[i] = [start_i, end_i] 表示第 i 次会议的开始和结束天数（包含首尾）。

返回员工可工作且没有安排会议的天数。

注意：会议时间可能会有重叠。

```cpp
class Solution {
public:
    int countDays(int days, vector<vector<int>>& a) {
        ranges::sort(a);
        int st = 0, ed = -1;
        for (auto & i : a) {
            int u = i[0], v = i[1];
            if (u <= ed) ed = max(ed, v);
            else days -= ed - st + 1, st = u, ed = v;
        }
        days -= ed - st + 1;
        return days;
    }
};
```

### 3170. 删除星号以后字典序最小的字符串

给你一个字符串 s 。它可能包含任意数量的 '*' 字符。你的任务是删除所有的 '*' 字符。

当字符串还存在至少一个 '*' 字符时，你可以执行以下操作：

删除最左边的 '*' 字符，同时删除该星号字符左边一个字典序 最小 的字符。如果有多个字典序最小的字符，你可以删除它们中的任意一个。

请你返回删除所有 '*' 字符以后，剩余字符连接而成的 字典序最小 的字符串。

```cpp
class Solution {
public:
    string clearStars(string s) {
        int n = s.size();
        bool del[n]; memset(del, 0, sizeof(del));
        vector<vector<int>> ids(26);
        for (int i = 0; i < n; i++) {
            if (s[i] == '*') {
                for (auto &v : ids) {
                    if (!v.empty()) {
                        del[v.back()] = true; v.pop_back();
                        break;
                    }
                }
            } else {
                ids[s[i]-'a'].push_back(i);
            }
        }        
        string ans;
        for (int i = 0; i < n; i++) if (s[i] != '*' && !del[i]) ans.push_back(s[i]);
        return ans;
    }
};
```

### 3171. 找到按位或最接近 K 的子数组

给你一个数组 nums 和一个整数 k 。你需要找到 nums 的一个 子数组 ，满足子数组中所有元素按位或运算 OR 的值与 k 的 绝对差 尽可能 小 。换言之，你需要选择一个子数组 nums[l..r] 满足 |k - (nums[l] OR nums[l + 1] ... OR nums[r])| 最小。

请你返回 最小 的绝对差值。

子数组 是数组中连续的 非空 元素序列。

```cpp
// 枚举。枚举子数组的终点，对于这个终点，其所有起点对应的或值数量最多只有32个
// 因为每或多一个数字，结果要么不变，要么二进制增加几位1，二进制最多有32位，于是最多有32种可能值。
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int ans = INT_MAX;
        set<int> s;
        for (auto i : nums) {
            vector<int> v ({i});
            for (auto j : s) v.push_back(j | i);
            s.clear();
            for (auto j : v) s.insert(j), ans = min(ans, abs(j - k));
        }
        return ans;
    }
};
```


## 第 401 场周赛

### 3178. 找出 K 秒后拿着球的孩子

给你两个 正整数 n 和 k。有 n 个编号从 0 到 n - 1 的孩子按顺序从左到右站成一队。

最初，编号为 0 的孩子拿着一个球，并且向右传球。每过一秒，拿着球的孩子就会将球传给他旁边的孩子。一旦球到达队列的 任一端 ，即编号为 0 的孩子或编号为 n - 1 的孩子处，传球方向就会 反转 。

返回 k 秒后接到球的孩子的编号。

```cpp
class Solution {
public:
    int numberOfChild(int n, int k) {
        int t = k % (n - 1);
        return k / (n - 1) % 2 ? n - 1 - t : t;
    }
};
```

### 3179. K 秒后第 N 个元素的值

给你两个整数 n 和 k。

最初，你有一个长度为 n 的整数数组 a，对所有 0 <= i <= n - 1，都有 a[i] = 1 。每过一秒，你会同时更新每个元素为其前面所有元素的和加上该元素本身。例如，一秒后，a[0] 保持不变，a[1] 变为 a[0] + a[1]，a[2] 变为 a[0] + a[1] + a[2]，以此类推。

返回 k 秒后 a[n - 1] 的值。

由于答案可能非常大，返回其对 109 + 7 取余 后的结果。

```cpp
using ll = long long;
const int mxn = 2001, mod = 1e9 + 7;

ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c;
    return ans;
}

ll fac[mxn], inv_fac[mxn];

auto init = []{
    fac[0] = 1;
    for (int i = 1; i < mxn; i++) fac[i] = fac[i-1] * i % mod;
    inv_fac[mxn-1] = qpow(fac[mxn-1], mod - 2, mod);    
    // 1/(i-1)! = 1/i! * i
    for (int i = mxn-1; i > 0; i--) inv_fac[i-1] = inv_fac[i] * i % mod;
    return 0;
}();

ll comb(ll n, ll k) { // C(n, k) = n! / (k! * (n-k)!);
    return fac[n] * inv_fac[k] % mod * inv_fac[n-k] % mod;
}

class Solution {
public:
    int valueAfterKSeconds(int n, int k) {
        return comb(n+k-1, k);
    }
};
```

### 3180. 执行操作可获得的最大总奖励 I

给你一个整数数组 rewardValues，长度为 n，代表奖励的值。

最初，你的总奖励 x 为 0，所有下标都是 未标记 的。你可以执行以下操作 任意次 ：

从区间 [0, n - 1] 中选择一个 未标记 的下标 i。
如果 rewardValues[i] 大于 你当前的总奖励 x，则将 rewardValues[i] 加到 x 上（即 x = x + rewardValues[i]），并 标记 下标 i。
以整数形式返回执行最优操作能够获得的 最大 总奖励。

```cpp
// f[i][j] = f[i-1][j] | f[i-1][j-v] j = [v, 2v)
class Solution {
public:
    int maxTotalReward(vector<int>& a) {        
        ranges::sort(a);
        a.erase(unique(a.begin(), a.end()), a.end());
        vector<int> f(4000+10);
        f[0] = 1;
        for (auto i : a) {
            for (int j = 2 * i - 1; j >= i; j--) f[j] |= f[j-i];
        }
        for (int i = f.size()-1; i >= 0; i--) if (f[i]) return i;
        return -1;
    }
}; 
```

### 3181. 执行操作可获得的最大总奖励 II

同上，但是范围更大。

```cpp
// f[i][j] = f[i-1][j] | f[i-1][j-v], j-v >= 0 && j-v < v
// 把f第一维优化掉，使用bitset表示
// 计算f[i]时，把f[i-1]的[0, v) 之间的值向左移动v位再与原bitset或起来
// j的上限是什么，2*mx-1
class Solution {
public:
    int maxTotalReward(vector<int>& a) {
        ranges::sort(a);
        a.erase(unique(a.begin(), a.end()), a.end());
        int n = a.size();
        bitset<100000+10> f(1);
        for (auto v : a) {
            int d = f.size() - v;
            f |= f << d >> d << v;
        }
        for (int i = f.size()-1; i >= 0; i--) if (f.test(i)) return i;
        return -1;
    }
};
```



## 第 402 场周赛

### 3184. 构成整天的下标对数目 I

给你一个整数数组 hours，表示以 小时 为单位的时间，返回一个整数，表示满足 i < j 且 hours[i] + hours[j] 构成 整天 的下标对 i, j 的数目。

整天 定义为时间持续时间是 24 小时的 整数倍 。

例如，1 天是 24 小时，2 天是 48 小时，3 天是 72 小时，以此类推。

```cpp
class Solution {
public:
    int countCompleteDayPairs(vector<int>& hours) {
        int ans = 0, n = hours.size();
        for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) ans += (hours[i] + hours[j]) % 24 == 0;
        return ans;
    }
};
```

### 3185. 构成整天的下标对数目 II

题目同 3184 但是数据更大。

```cpp
class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        long long ans = 0;
        vector<int> a(24);
        for (auto i : hours) ans += a[(24-i%24)%24], a[i%24]++;
        return ans;
    }
};
```

### 3186. 施咒的最大总伤害

一个魔法师有许多不同的咒语。

给你一个数组 power ，其中每个元素表示一个咒语的伤害值，可能会有多个咒语有相同的伤害值。

已知魔法师使用伤害值为 power[i] 的咒语时，他们就 不能 使用伤害为 power[i] - 2 ，power[i] - 1 ，power[i] + 1 或者 power[i] + 2 的咒语。

每个咒语最多只能被使用 一次 。

请你返回这个魔法师可以达到的伤害值之和的 最大值 。

```cpp
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        map<int, int> m;
        for (auto i : power) m[i]++;

        vector<pair<int, int>> v(m.begin(), m.end());

        int n = v.size();
        vector<long long> dp(n + 1);
        
        for (int i = 0, j = 0; i < n; i++) {
            auto &[x, c] = v[i];
            while (j < i && v[j].first < x - 2) j++;
            dp[i+1] = max(dp[i], dp[j] + (long long)x * c);
        }
        return dp[n];
    }
};
```

### 3187. 数组中的峰值

数组 arr 中 大于 前面和后面相邻元素的元素被称为 峰值 元素。

给你一个整数数组 nums 和一个二维整数数组 queries 。

你需要处理以下两种类型的操作：

- queries[i] = [1, li, ri] ，求出子数组 nums[li..ri] 中 峰值 元素的数目。
- queries[i] = [2, indexi, vali] ，将 nums[indexi] 变为 vali 。
  
请你返回一个数组 answer ，它依次包含每一个第一种操作的答案。

注意：子数组中 第一个 和 最后一个 元素都 不是 峰值元素。

```cpp
using ll = int;

struct STN { ll sum; };
struct ST {
    ll mn, mx;
    vector<STN> a;
    ST(ll mn = 0, ll mx = 1e5) : mn(mn), mx(mx), a(vector<STN>((mx - mn) * 4)){};

    void build(vector<ll> &v) { build(1, mn, mx, v); }
    void replace(ll l, ll r, ll d) { replace(1, mn, mx, l, r, d); }
    void increase(ll l, ll r, ll d) { increase(1, mn, mx, l, r, d); }
    ll query(ll l, ll r) { return query(1, mn, mx, l, r); }

    void build(ll k, ll l, ll r, vector<ll> &v) {
        if (l == r) { a[k] = {v[l]}; return; }
        ll lc = k << 1, rc = lc | 1, m = (l + r) >> 1;
        build(lc, l, m, v);
        build(rc, m + 1, r, v);
        pushup(k, lc, rc);
    }
    void replace(ll k, ll l, ll r, ll L, ll R, ll D) {
        if (l == r) { a[k].sum = (r - l + 1) * D; return; }
        ll lc = k << 1, rc = lc | 1, m = (l + r) >> 1;
        if (m >= L) replace(lc, l, m, L, R, D);
        if (m + 1 <= R) replace(rc, m + 1, r, L, R, D);
        pushup(k, lc, rc);
    }
    void increase(ll k, ll l, ll r, ll L, ll R, ll D) {
        if (l == r) { a[k].sum += (r - l + 1) * D; return; }
        ll lc = k << 1, rc = lc | 1, m = (l + r) >> 1;
        if (m >= L) increase(lc, l, m, L, R, D);
        if (m + 1 <= R) increase(rc, m + 1, r, L, R, D);
        pushup(k, lc, rc);
    }
    inline void pushup(ll k, ll lc, ll rc) {
        a[k].sum = a[lc].sum + a[rc].sum;
    }
    ll query(ll k, ll l, ll r, ll L, ll R) {
        if (L <= l && r <= R) return a[k].sum;
        ll lc = k << 1, rc = lc | 1, m = (l + r) >> 1, ans = 0;
        if (m >= L) ans += query(lc, l, m, L, R);
        if (m + 1 <= R) ans += query(rc, m + 1, r, L, R);
        return ans;
    }
};

class Solution {
   public:
    vector<int> countOfPeaks(vector<int> &a, vector<vector<int>> &queries) {
        int n = a.size();
        ST st(0, n - 1);

        auto v = vector<int>(n);
        for (int i = 1; i < n - 1; i++) v[i] = a[i] > a[i - 1] && a[i] > a[i + 1];
        st.build(v);

        auto f = [&](int id) {
            auto ok = id - 1 >= 0 && id + 1 < n;
            if (!ok) return;
            int nv = a[id] > a[id - 1] && a[id] > a[id + 1] ? 1 : 0;
            st.replace(id, id, nv);
        };

        vector<int> ans;
        for (auto &q : queries) {
            int t = q[0];
            if (t == 1) {
                if (q[1] + 1 <= q[2] - 1)
                    ans.push_back(st.query(q[1] + 1, q[2] - 1));
                else
                    ans.push_back(0);
            } else {
                int i = q[1], val = q[2];
                a[i] = val;
                for (int j = i-1; j <= i+1; j++) f(j);
            }
        }
        return ans;
    }
};
```

## 第 403 场周赛

### 3194. 最小元素和最大元素的最小平均值

你有一个初始为空的浮点数数组 averages。另给你一个包含 n 个整数的数组 nums，其中 n 为偶数。

你需要重复以下步骤 n / 2 次：

* 从 nums 中移除 最小 的元素 minElement 和 最大 的元素 maxElement。
* 将 (minElement + maxElement) / 2 加入到 averages 中。

返回 averages 中的 最小 元素。

```cpp
class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        ranges::sort(nums);
        int ans = INT_MAX;
        for (int i = 0, j = nums.size()-1; i < j; i++, j--) ans = min(ans, nums[i] + nums[j]);
        return ans / 2.0;
    }
};
```

### 3195. 包含所有 1 的最小矩形面积 I

给你一个二维 二进制 数组 grid。请你找出一个边在水平方向和竖直方向上、面积 最小 的矩形，并且满足 grid 中所有的 1 都在矩形的内部。

返回这个矩形可能的 最小 面积。

```cpp
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int x1 = m-1, x2 = 0, y1 = n-1, y2 = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    x1 = min(x1, i), x2 = max(x2, i);
                    y1 = min(y1, j), y2 = max(y2, j);
                }
            }
        }
        return (x2 - x1 + 1) * (y2 - y1 + 1);
    }
};
```

### 3196. 最大化子数组的总成本

给你一个长度为 n 的整数数组 nums。

子数组 nums[l..r]（其中 0 <= l <= r < n）的 成本 定义为：

cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)r − l

你的任务是将 nums 分割成若干子数组，使得所有子数组的成本之和 最大化，并确保每个元素 正好 属于一个子数组。

具体来说，如果 nums 被分割成 k 个子数组，且分割点为索引 i1, i2, ..., ik − 1（其中 0 <= i1 < i2 < ... < ik - 1 < n - 1），则总成本为：

cost(0, i1) + cost(i1 + 1, i2) + ... + cost(ik − 1 + 1, n − 1)

返回在最优分割方式下的子数组成本之和的最大值。

注意：如果 nums 没有被分割，即 k = 1，则总成本即为 cost(0, n - 1)。

```cpp
// f[i]：[0,i]的最大成本
// f[i] = max(a[i]+f[i-1], -a[i]+a[i-1]+f[i-2])，i从1开始
// 但是f[i-2]下标会出现-1，把f的下标都往右加1，答案为f[n]
class Solution {
public:
    long long maximumTotalCost(vector<int>& nums) {
        int n = nums.size();
        vector<long long> f(n+1);
        f[1] = nums[0];
        for (int i = 1; i < n; i++) {
            f[i+1] = max(nums[i] + f[i], -nums[i] + nums[i-1] + f[i-1]);
        }
        return f[n];
    }
};
```

### 3197. 包含所有 1 的最小矩形面积 II

给你一个二维 二进制 数组 grid。你需要找到 3 个 不重叠、面积 非零 、边在水平方向和竖直方向上的矩形，并且满足 grid 中所有的 1 都在这些矩形的内部。

返回这些矩形面积之和的 最小 可能值。

注意，这些矩形可以相接。

```cpp
// 枚举切割位置，枚举水平切割和竖直切割两种方式
class Solution {
public:
    int f(int k, int x1, int x2, int y1, int y2, vector<vector<int>> &grid) {
        int ans = INT_MAX >> 1;

        if (k == 1) {
            int mn1 = x2, mx1 = x1, mn2 = y2, mx2 = y1, found = 0;
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    if (grid[i][j]) {
                        found = 1;
                        mn1 = min(mn1, i), mx1 = max(mx1, i);
                        mn2 = min(mn2, j), mx2 = max(mx2, j);
                    }
                }
            }
            if (found) ans = (mx1 - mn1 + 1) * (mx2 - mn2 + 1);
            return ans;            
        }

        for (int i = x1; i < x2; i++) {
            for (int j = 1; j < k; j++) {
                ans = min(ans, f(j, x1, i, y1, y2, grid) + f(k-j, i+1, x2, y1, y2, grid));
            }
            
        }
        for (int i = y1; i < y2; i++) {
            for (int j = 1; j < k; j++) {
                ans = min(ans, f(j, x1, x2, y1, i, grid) + f(k-j, x1, x2, i+1, y2, grid));
            }
        }

        return ans;
    }

    int minimumSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        return f(3, 0, m-1, 0, n-1, grid);
    }
};
```

## 第 404 场周赛

### 3200. 三角形的最大高度

给你两个整数 red 和 blue，分别表示红色球和蓝色球的数量。你需要使用这些球来组成一个三角形，满足第 1 行有 1 个球，第 2 行有 2 个球，第 3 行有 3 个球，依此类推。

每一行的球必须是 相同 颜色，且相邻行的颜色必须 不同。

返回可以实现的三角形的 最大 高度。

```cpp
class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        int odd = 0, even = 0;
        for (int i = 1; ; i++) {
            (i&1 ? odd : even) += i;
            if ((odd > red || even > blue) && (odd > blue || even > red)) return i-1;
        }
        return 0;
    }
};
```

### 3201. 找出有效子序列的最大长度 I

给你一个整数数组 nums。

nums 的子序列 sub 的长度为 x ，如果其满足以下条件，则称其为 有效子序列：

(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2
返回 nums 的 最长的有效子序列 的长度。

一个 子序列 指的是从原数组中删除一些元素（也可以不删除任何元素），剩余元素保持原来顺序组成的新数组。

```cpp
下一题的特殊情况。
```

### 3202. 找出有效子序列的最大长度 II

给你一个整数数组 nums 和一个 正 整数 k 。nums 的一个 子序列 sub 的长度为 x ，如果其满足以下条件，则称其为 有效子序列 ：

(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k

返回 nums 的 最长有效子序列 的长度。

```cpp
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int ans = 0;
        for (int m = 0; m < k; m++) {            
            vector<int> f(k);
            for (auto i : nums) {
                i %= k;
                f[i] = 1 + f[(m - i + k) % k];
                ans = max(ans, f[i]);
            }
        }
        return ans;
    }
};
```

### 3203. 合并两棵树后的最小直径

给你两棵 无向 树，分别有 n 和 m 个节点，节点编号分别为 0 到 n - 1 和 0 到 m - 1 。给你两个二维整数数组 edges1 和 edges2 ，长度分别为 n - 1 和 m - 1 ，其中 edges1[i] = [ai, bi] 表示在第一棵树中节点 ai 和 bi 之间有一条边，edges2[i] = [ui, vi] 表示在第二棵树中节点 ui 和 vi 之间有一条边。

你必须在第一棵树和第二棵树中分别选一个节点，并用一条边连接它们。

请你返回添加边后得到的树中，最小直径 为多少。

一棵树的 直径 指的是树中任意两个节点之间的最长路径长度。

```cpp
int diameter(vector<vector<int>> &edges) {
    int n = edges.size() + 1;
    vector<vector<int>> g(n);
    for (auto &e : edges) {
        int u = e[0], v = e[1];
        g[u].push_back(v), g[v].push_back(u);
    }

    int ans = 0;
    function<int(int, int)> dfs = [&](int x, int fa) -> int {
        int mx = 0;
        for (auto y : g[x]) {
            if (y != fa) {
                int sub = dfs(y, x) + 1;
                ans = max(ans, mx + sub);
                mx = max(mx, sub);
            }
        }
        return mx;
    };
    dfs(0, -1);
    return ans;
}

class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int d1 = diameter(edges1), d2 = diameter(edges2);
        return max({d1, d2, (d1+1)/2 + (d2+1)/2 + 1});
    }
};
```

## 第 406 场周赛

### 100367. 切蛋糕的最小总开销 II

有一个 m x n 大小的矩形蛋糕，需要切成 1 x 1 的小块。

给你整数 m ，n 和两个数组：

* horizontalCut 的大小为 m - 1 ，其中 horizontalCut[i] 表示沿着水平线 i 切蛋糕的开销。
* verticalCut 的大小为 n - 1 ，其中 verticalCut[j] 表示沿着垂直线 j 切蛋糕的开销。

一次操作中，你可以选择任意不是 1 x 1 大小的矩形蛋糕并执行以下操作之一：

* 沿着水平线 i 切开蛋糕，开销为 horizontalCut[i] 。
* 沿着垂直线 j 切开蛋糕，开销为 verticalCut[j] 。

每次操作后，这块蛋糕都被切成两个独立的小蛋糕。

每次操作的开销都为最开始对应切割线的开销，并且不会改变。

请你返回将蛋糕全部切成 1 x 1 的蛋糕块的 最小 总开销。

```cpp
class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        vector<pair<int, int>> v;
        for (auto i : horizontalCut) v.emplace_back(i, 0);
        for (auto i : verticalCut) v.emplace_back(i, 1);
        ranges::sort(v, greater<>());
        long long ans = 0, c0 = 1, c1 = 1;
        for (auto &[x, y] : v) {
            if (y == 0) ans += (long long)x * c1, c0++;
            else ans += (long long)x * c0, c1++;
        }
        return ans;
    }
};
```