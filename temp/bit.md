# 树状数组（BIT）

数组c的每个元素c[i]表示从a[i]起往前若干个元素的和：a[i] + a[i-1] + ... + a[x]，[x, i]这里的x为i的二进制表示中去掉最低位1后的下一个数字。

比如c[6]，6的二进制为110，去掉最低位1位100=4，所以起始数字为 101+1=4+1=5, 所以c[6] = a[6] + a[5]
  
https://oi-wiki.org/ds/fenwick/

## 一维树状数组
 
参数n为元素数量，实现中数组下标从1开始（构造了一个长度为n+1的数组）。

```cpp
class BIT {
public:
    BIT(int n): c(n + 1) {}
    void update(int i, int val = 1) { while (i < c.size()) c[i] += val, i += i & -i ; }
    int sum(int i) { int ans = 0; while (i) ans += c[i], i -= i & -i; return ans; }
    int query(int l, int r) { return sum(r) - sum(l - 1); }

private:
    vector<int> c;    
};
```