# 并查集 (disjoint set)

```cpp
struct DisjointSet {
    vector<int> pa, size;
    DisjointSet(int n): pa(n), size(n, 1) { for (int i = 0; i < n; i++) pa[i] = i; }
    int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        pa[y] = x; size[x] += size[y];
    }
};
```
