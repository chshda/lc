# 背包

## 0-1 背包

刚好装满，初始化f[0]为1，表示不选择任何物品的情况下，容量为0时方法数为1，容量大于0时方法数为0（不可能）

```cpp
int f[k]; memset(f, 0, sizeof(f));
f[0] = 1;
for (auto w : a) {
    for (int i = k-1; i >= w; i--) f[i] += f[i-w]; // 倒序
}
```

不超过容量，初始化全部为1，表示不选择任何物品的情况下，容量不超过i的方法数为1

```cpp
int f[k]; fill(f, f+k, 1);
for (auto w : a) {
    for (int i = k-1; i >= w; i--) f[i] += f[i-w]; // 倒序
}
```
