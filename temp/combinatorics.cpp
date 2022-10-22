#include "header.h"

// 阶乘和阶乘逆元
ll fac[N], inv[N];

// 排列数
// A(n,m) = n!/(n-m)! % mod
inline ll getA(ll n, ll m) { return fac[n] * inv[n - m] % mod; }

// 组合数
// C(n,m) = n!/((n-m)!*m!) % mod
inline ll getC(ll n, ll m) { return fac[n] * inv[n - m] % mod * inv[m] % mod; }

/**
 * 杨辉三角求组合数
 *
 * 当数据规模比较小时：C(n,m) = C(n-1, m) + C(n-1, m-1)
 **/
int yh(int n) {
    int C[n + 1][n + 1];
    for (int i = 0; i <= n; i++) C[i][i] = 1, C[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
}

/**
 * Lucas定理求组合数
 *
 * 当n，m很大时，可以用Lucas定理降数据。
 */
inline ll lucas(ll n, ll m) {
    if (n < mod && m < mod) return getC(n, m);
    return lucas(n / mod, m / mod) * getC(n % mod, m % mod) % mod;
}

/**
 * 逆元
 *
 * 模意义下，1个数a如果有逆元x，那么除以a相当于乘以x。
 * 一个数有逆元的充分必要条件是gcd(a,p)=1，此时逆元唯一存在。
 **/

/**
 * 费马小定理求逆元
 *
 * 如果p是质数，整数a不是p的倍数，则有a^(p-1) ≡ 1 (mod p)。
 * a的逆元为a^(p-2)，使用二分快速幂。
 **/
ll quick_power(ll base, ll n) {
    ll ans = 1;
    while (n > 0) {
        if (n & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        n >>= 1;
    }
    return ans;
}
ll reverse_feimat(ll a) { return quick_power(a, mod - 2); }

/**
 * 拓展欧几里得求逆元
 *
 * 拓展欧几里得：gcd(a,b) = a * x + b * y
 * 如果a,b互质，则gcd(a,b)=1，则ax+by=1。
 **/
ll reverse_egcd(ll a) {
    typedef function<ll(ll, ll, ll &, ll &)> fun;
    fun egcd = [&](ll a, ll b, ll &x, ll &y) -> ll {
        if (b == 0) {
            x = 1, y = 0;
            return a;
        }
        ll d = egcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    };

    ll x, y;
    ll d = egcd(a, mod, x, y);
    return d == 1 ? (x % mod + mod) % mod : -1;
}

/**
 * (TODO)欧拉定理求逆元
 **/

/**
 * 阶乘逆元
 **/
void getfac(ll n) {
    ll fac[n + 1], inv[n + 1];
    fac[0] = inv[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = quick_power(fac[i], mod - 2);
    }
}

/**
 * 例题
 *
 * 在1-n之间随机生成长度为n的整数序列，请问正好含有n-1个不同的整数的方案数
 * https://ac.nowcoder.com/acm/contest/6037/B
 *
 *
 **/