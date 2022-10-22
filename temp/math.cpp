#include "header.h"

/**
 * GCD, LCM
 *
 * 常用思路：枚举1-n，然后i的倍数i,2i,3i...，复杂度n/1+n/2+...1=nlogn(调和级数)
 **/
ll gcd(ll x, ll y) {
    if (!x || !y) return x > y ? x : y;
    for (ll t; t = x % y; x = y, y = t) 42;
    return y;
}

ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }

ll qgcd(ll x, ll y) {
    if (!x || !y) return max(x, y);
    if (!(x & 1) && !(y & 1)) return qgcd(x >> 1, y >> 1) << 1;
    if (!(x & 1)) return qgcd(x >> 1, y);
    if (!(y & 1)) return qgcd(x, y >> 1);
    return qgcd(abs(x - y), min(x, y));
}

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = egcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 判断一个数是否为质数
bool is_prime(ll n) {
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return n >= 2;
}

/**
 * 埃拉托斯特尼筛法 Sieve of Eratosthenes
 *
 * pi[n]：质数个数
 **/
void sieve(ll n) {
    bool is[n + 1];  // 数字i是不是素数
    memset(is, true, sizeof(is));
    is[0] = is[1] = false;

    ll prime[n + 1], cnt = 0;  // 素数数组，素数个数
    repi(i, 2, n) {
        if (!is[i]) continue;
        prime[cnt++] = i;
        for (int j = 2 * i; j <= n; j += i) is[j] = false;
    }

    int pi[n + 1] = {0};  // 小于等于i的素数个数
    repi(i, 2, n) pi[i] = pi[i - 1] + (is[i] ? 1 : 0);
}

/**
 * 线性筛素数（Euler筛法）
 *
 * 每个合数只会被他的第一个质因子筛掉。
 *
 * 在筛素数的时候，如果i % prime[j] == 0，i之前被prime[j]筛过了
 * 由于 prime 里面质数是从小到大的，所以 i
 * 乘上其他的质数的结果一定也是 pri[j] 的倍数
 * 它们都被筛过了，就不需要再筛了，所以这里直接 break 掉就好了
 * https://oi-wiki.org/math/number-theory/sieve/#%E7%BA%BF%E6%80%A7%E7%AD%9B%E6%B3%95
 **/
void sieve_euler(ll n) {
    bool is[n + 1];  // 数字i是不是素数
    memset(is, true, sizeof(is));
    is[0] = is[1] = false;

    ll prime[n], cnt = 0;  // 素数数组，素数个数
    repi(i, 2, n) {
        if (is[i]) prime[cnt++] = i;
        rep(j, 0, cnt) {
            ll k = i * prime[j];
            if (k > n) break;
            is[k] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

struct factor {
    ll p, e;
};
vector<factor> factorize(ll x) {
    vector<factor> ans;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i != 0) continue;
        ll e = 0;
        while (x % i == 0) e++, x /= i;
        ans.push_back({i, e});
    }
    if (x > 1) ans.push_back({x, 1});
    return ans;
}

vector<ll> prime_divisors(ll x) {
    vector<ll> primes;
    if (x & 1 == 0) {
        primes.push_back(2);
        while (x & 1 == 0) x >>= 1;
    }
    for (ll i = 3; i * i <= x; i++) {
        if (x % i != 0) continue;
        primes.push_back(i);
        while (x % i == 0) x /= i;
    }
    return primes;
}
