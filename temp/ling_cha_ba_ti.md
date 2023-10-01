# 灵茶八题代码
[https://www.luogu.com.cn/blog/endlesscheng/post-ling-cha-ba-ti-ti-mu-lie-biao](https://www.luogu.com.cn/blog/endlesscheng/post-ling-cha-ba-ti-ti-mu-lie-biao)

## 1 子数组元素和的元素和

贡献法。 包含 $a[i]$ 的子数组的左端点有 $i+1$ 个，右端点有 $n-i$ 个，根据乘法原理，有 $(i+1)\cdot(n-i)$ 个子数组包含 $a[i]$，所以 $a[i]$ 对答案的贡献为 $(i+1)\cdot(n-i)\cdot a[i]$。

```cpp
#include "bits/stdc++.h"
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];
    
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += a[i] * (i + 1LL) * (n - i);
    cout << ans << endl;
}
```

## 2 子数组异或和的异或和

贡献法，同上。更强的结论是：

* 当 $n$ 是偶数时，$i+1$ 和 $n-i$ 必定一奇一偶，所以 $(i+1)(n-i)$ 是偶数，答案为 $0$。
* 当 $n$ 是奇数时，如果 $i$ 为奇数，那么 $i+1$ 和 $n-i$ 都是偶数；如果 $i$ 为偶数，那么 $i+1$ 和 $n-i$ 都是奇数，所以只有 $i$ 为偶数时 $(i+1)(n-i)$ 才是奇数。所以，答案为所有偶数下标的 $a[i]$ 的异或和。

```cpp
#include "bits/stdc++.h"
using namespace std;

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];
    
    int ans = 0;
    for (int i = 0; i < n; i++) if ((i + 1) * (n - i) & 1) ans ^= a[i];
    cout << ans << endl;
}
```

## 3 子数组异或和的元素和

二进制拆位。如果数组中只有 $0$ 和 $1$，要怎么做？相当于计算有多少个子数组，异或和等于 $1$。

计算前缀异或和数组 $s$（长为 $n+1$），相当于从 $s$ 中选两个数，异或等于 $1$。
这两个数必须恰好一个是 $1$，另一个是 $0$。

假设 $s$ 中有 $c$ 个 $1$，那么就有 $n+1-c$ 个 $0$，所以答案为 $c\cdot(n+1-c)$。
一般地，统计 $s$ 中第 $k$ 位的 $1$ 的个数 $c$，那么这一位对答案的贡献是 $c\cdot(n+1-c)\cdot 2^k$。

```cpp
#include "bits/stdc++.h"
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];
    
    ll ans = 0;
    for (int k = 0; k < 31; k++) {
        int pre[n+1]; pre[0] = 0;
        for (int i = 1; i <= n; i++) pre[i] = pre[i-1] ^ (a[i-1] >> k & 1);
        ll cnt = accumulate(pre, pre + n + 1, 0);
        ans += (cnt * (n + 1 - cnt)) << k;
    }
    cout << ans << endl;
}
```

## 4 子数组元素和的异或和

借位拆位。计算出前缀和数组 $s$。考虑所有的【两个前缀和相减】的结果，二进制从低到高第 $k$ 位有多少个 $1$。

* 例如 $k=2$ 时，相当于减法的结果的低 $3$ 位在 $[100,111]$ 中。

* 但如果只考虑前缀和的低 $3$ 位，$1000-1=111$ 本来应该满足条件，但是只取低 $3$ 位就变成 $0-1$ 了。如果前缀和 $\ge 2^3$，我们可以在取低 $3$ 位后补一个 $2^3$，这样 $1000-1=111$ 就是满足要求的。但是，还有可能出现 $1111-1=1110$ 这样的情况，所以减法的结果应当在 $[100,111]\cup [1100,1111]$ 中。

这可以用树状数组/名次树维护统计。

```cpp
#include "bits/stdc++.h"
using namespace std;

class BIT {
public:
    BIT(int n): c(n + 1) {}
    void update(int i, int val = 1) { while (i < c.size()) c[i] += val, i += i & -i ; }
    int sum(int i) { int ans = 0; while (i) ans += c[i], i -= i & -i; return ans; }
    int query(int l, int r) { return sum(r) - sum(l - 1); }
private:
    vector<int> c;    
};


int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];

    int pre[n+1]; pre[0] = 0;
    partial_sum(a, a+n, pre+1);
    
    int ans = 0;
    for (int k = 0, mxk = log2(pre[n]) + 1; k <= mxk; k++) {
        int cnt = 0, mn = 1 << k, mx = (1 << (k+1)) - 1;
        BIT bit(mx+2);
        for (int i = 0; i <= n; i++) {
            int t = pre[i] & mx, ot = t; // 后k位
            if (pre[i] > t) t |= 1 << (k+1); // 借位

            auto count = [&](int mn, int mx) {
                int st = t - mx, ed = t - mn;
                if (ed < 0 || st > mx) return;
                if (st < 0) st = 0;
                if (ed > mx) ed = mx;
                cnt ^= bit.query(st+1, ed+1);
            };
            
            count(mn, mx);
            count(mn | (1 << (k+1)), mx | (1 << (k+1)));

            bit.update(ot+1); // 只记录后k位的数值（没有借位），加1保证数值>=1
        }
        if (cnt & 1) ans ^= 1 << k;
    }
    cout << ans;
}
```

## 5 子序列的元素和的元素和

贡献法。包含 $a[i]$ 的子序列有 $2^{n-1}$ 个。所以 $a[i]$ 对答案的贡献为 $2^{n-1}\cdot a[i]$。所以答案为 $2^{n-1}\cdot \sum a[i]$。

```cpp
#include "bits/stdc++.h"
using namespace std;

using ll = long long;
static const int mod = 1e9 + 7;

ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c;
    return ans;
}

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];
        
    ll ans = accumulate(a, a+n, 0LL) % mod;
    ans = qpow(2, n-1, mod) * ans % mod;
    cout << ans << endl;
}
```

## 6 子序列的异或和的异或和

贡献法。当 $n=1$ 时，答案为 $a[0]$。当 $n\ge 2$ 时，由于 $2^{n-1}$ 是偶数，所以答案为 $0$。

```cpp
#include "bits/stdc++.h"
using namespace std;

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];
    cout << (n == 1 ? a[0] : 0) << endl;
}
```

## 7 子序列异或和的元素和

二进制拆位。如果第 $k$ 位都是 $0$，那么对答案的贡献是 $0$。如果第 $k$ 位有 $c$ 个 $1$，用数学归纳法可以证明，从 $c$ 个数中选偶数个数的方案数是 $2^{c-1}$，选奇数个数的方案数也是 $2^{c-1}$。再算上 $0$，那么异或和为 $0$ 的子序列有 $2^{n-1}$ 个，异或和为 $1$ 的子序列也有 $2^{n-1}$ 个，所以这一位的贡献是 $2^{n-1}\cdot 2^k$。

根据递推式

* $f[n][0] = f[n-1][0] + f[n-1][1]$
* $f[n][1] = f[n-1][0] + f[n-1][1]$

可知n个数选奇数个数和选偶数个数的方案数一样，为 $2^n / 2 = 2 ^ (n-1)$。

```cpp
#include "bits/stdc++.h"
using namespace std;

using ll = long long;
static const int mod = 1e9 + 7;

ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % c) if (b & 1) ans = ans * a % c;
    return ans;
}

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];

    ll ans = 0;
    for (int k = 0; k < 31; k++) {
        int cnt = 0; 
        for (auto i : a) cnt += i >> k & 1;
        if (cnt != 0) ans = (ans + (qpow(2, n - 1, mod) << k) % mod) % mod;
    }
    cout << ans;
}
```

## 8 子序列元素和的异或和

0-1 背包。定义 $f[i][j]$ 表示从前 $i$ 个数中选出元素和为 $j$ 的方案数的奇偶性。

* 初始值 $f[0][0]=1$，其余为 $0$。
* 状态转移方程为 $f[i+1][j]=f[i][j]\oplus f[i][j-a[i]]$。
* 答案为 $f[n][j]=1$ 的 $j$ 的异或和。

```cpp
#include "bits/stdc++.h"
using namespace std;

using ll = long long;
static const int mod = 1e9 + 7;

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];

    int m = accumulate(a, a+n, 0) * 2;
    int dp[m]; // dp[i][j]: 0-ith, sum=j, cnt(odd/even)
    memset(dp, 0, sizeof(dp)); dp[0] = 1; 
    for (auto i : a) {
        for (int j = m-1; j >= i; j--) dp[j] ^= dp[j-i];
    }    

    ll ans = 0;
    for (int i = 1; i < m; i++) if (dp[i]) ans ^= i;
    cout << ans;
}
```
