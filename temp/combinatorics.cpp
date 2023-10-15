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