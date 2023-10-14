// Source: https://oj.leetcode.com/problems/sqrtx/

class Solution {
public:
    int sqrt1(int x) { //二分
        if (x == 0) return 0;
        
        unsigned long long st = 0, ed = x, mid, tem;
        while (st < ed)
        {
            mid = st + ((ed - st) >> 1);
            if ((tem = mid * mid) == x) return mid; //平方根为正数
            else if(x > tem) st = mid + 1;
            else ed = mid - 1;
        }
        if ((tem = st * st) > x) return st - 1; //太大
        else return st;
    }
    
    
    int sqrt(int x) { //牛顿法
        if (x == 0) return 0;

        double pre = -1, cur = 1; //分别为xn和xn+1
        while (fabs(cur - pre) > 1e-6)
            pre = cur, cur = x / (2 * cur) + cur / 2;
        return int(cur);
    }
    
    int sqrt2(int x) {
        return int(pow(double(x), 0.5));
    }
};