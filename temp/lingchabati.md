# 灵茶八题代码
[https://www.luogu.com.cn/blog/endlesscheng/post-ling-cha-ba-ti-ti-mu-lie-biao](https://www.luogu.com.cn/blog/endlesscheng/post-ling-cha-ba-ti-ti-mu-lie-biao)
## 1 子数组元素和的元素和

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
```cpp
#include "bits/stdc++.h"
using namespace std;

class BIT {
public:
    BIT(int n): c(n + 1) {}

    void update(int i, int val = 1) {
         while (i < c.size()) c[i] += val, i += i & -i ;
    }

    int sum(int i) {
        int ans = 0;
        while (i) ans += c[i], i -= i & -i;
        return ans;
    }

    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }

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
            int t = pre[i] & mx, ot = t;
            if (pre[i] > t) t |= 1 << (k+1);

            auto count = [&](int mn, int mx) {
                int st = t - mx, ed = t - mn;
                if (ed < 0 || st > mx) return;
                if (st < 0) st = 0;
                if (ed > mx) ed = mx;
                cnt ^= bit.query(st+1, ed+1);
            };
            
            count(mn, mx);
            count(mn | (1 << (k+1)), mx | (1 << (k+1)));

            bit.update(ot+1);
        }
        if (cnt & 1) ans ^= 1 << k;
    }
    cout << ans;
}
```
## 5 子序列的元素和的元素和
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
