#include "header.h"

/**
 * 树状数组
 * 
 * 数组c的每个元素c[i]表示从a[i]起往前若干个元素的和：a[i] + a[i-1] + ... + a[x]
 * [x, i]这里的x为i的二进制表示中去掉最低位1后的下一个数字
 * 比如c[6]，6的二进制为110，去掉最低位1位100=4，所以c[6] = (4,6]的和 = a[5] + a[6]
 * 
 * https://oi-wiki.org/ds/fenwick/
 **/
void bit(int n) {
    int c[n+1];  // 数组下标从1开始

    auto lowbit = [&](int x) -> int { return x & -x; };
    
    auto update = [&](int i, int val) -> void {
        while (i <= n) c[i] += val, i += lowbit(i);
    };

    auto sum = [&](int i) -> int {
        int ans = 0;
        while (i) ans += c[i], i -= lowbit(i);
        return ans;
    };

    auto query = [&](int l, int r) -> int {
        return sum(r) - sum(l - 1); // [l, r]
    };
};
