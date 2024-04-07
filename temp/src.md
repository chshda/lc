# 题解

## 3046. 分割数组

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

## 3047. 求交集区域内的最大正方形面积

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

## 3048. 标记所有下标的最早秒数 I

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

## 3049. 标记所有下标的最早秒数 II

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
class Bit {
public:
    Bit(int n): c(n + 1) {}
    void update(int i, int val = 1) { while (i < c.size()) c[i] += val, i += i & -i ; }
    int sum(int i) { int ans = 0; while (i) ans += c[i], i -= i & -i; return ans; }
    int query(int l, int r) { return sum(r) - sum(l - 1); }

private:
    vector<int> c;    
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        auto t = nums;
        ranges::sort(t);
        t.erase(unique(t.begin(), t.end()), t.end());

        auto f = [&](int x) {
            return lower_bound(t.begin(), t.end(), x) - t.begin() + 1;
        };

        int n = t.size();
        vector<int> v1, v2;
        Bit t1(n), t2(n);
        v1.push_back(nums[0]), t1.update(f(nums[0]));
        v2.push_back(nums[1]), t2.update(f(nums[1]));

        for (int i = 2; i < nums.size(); i++) {
            int v = f(nums[i]);
            int c1 = t1.query(v+1, n), c2 = t2.query(v+1, n);
            if (c1 > c2 || (c1 == c2 && (v1.size() <= v2.size()))) {
                v1.push_back(nums[i]), t1.update(v);
            } else {
                v2.push_back(nums[i]), t2.update(v);
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