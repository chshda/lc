
#include "header.h"

/**
 * 二分查找
 *
 * 查找满足条件的最小的数值：0----false-----ans----true----n
 * mid要是落在左边false的区间范围内，让l=mid+1来丢弃mid或者mid左边的数值
 * mid要是落在右边true的区间范围内，让r=mid来丢弃mid右边的数值
 *
 * 我们的[l,r)本质上是左闭右开区间，即右边不包括边界，r=mid看上去可能把最优值漏在区间之外。
 * 假如mid即为最优值，由于mid为true我们设置了r=mid，在接下来的循环中，mid会不断地命中false，
 * 从而导致l不断地更新为mid+1，最终(l,r)距离为1的时候，mid的值会是l，
 * 然后l更新为mid+1后，达到l==r找到最优值并退出循环。
 **/
bool check(int x);
void bin1(int l, int r) {
    while (l < r) {
        int m = (l + r) >> 1;
        if (check(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
}

/**
 * 二分查找
 *
 * 查找满足条件的最大的数值：0----true-----ans----false----n
 * mid要是落在左边true的区间范围内，让l=mid来取得mid或者mid右边的数值
 * mid要是落在右边false的区间范围内，让r=mid-1来丢弃mid及其右边的数值
 *
 * 因为l=mid的赋值，普通的(l+r)/2方法计算的mid是偏向左边的，
 * 即当l和r相差1时，mid的值为l，此时如果循环l=mid时(l,r)会保持不变而导致死循环，
 * 可以采用(l+r+1)/2的方法计算mid让mid偏向右边。
 *
 * r=mid-1不能写成r=mid，因为mid的值是偏向右边的，mid有可能跟r相同，
 * r=mid的话会导致(l,r)保持不变导致死循环。
 *
 * 同时也不用担心会错过最优值，假如mid是false而mid-1是最优值，我们的[l,r)本质上是左闭右开区间，
 * 即右边不包括边界，r=mid-1看上去好像把最优值漏在了区间之外。
 * 但是在接下来的循环中，mid会不断地命中true，从而导致l不断地更新为mid，由于mid是偏右的，
 * 最终(l,r)距离为1的时候，mid的值会是r，然后l会更新为r从而l==r找到最优值并退出循环。
 **/
bool check(int x);
void bin2(int l, int r) {
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (check(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
}