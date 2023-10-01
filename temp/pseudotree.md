# 基环树 (pseudotree)

基环树（环套树）， n 个点 n 条边的图，树加一条边。

* 内向基环树：每个点出度为1（因此每个环上点的子树，儿子指向父亲）
* 外向基环树：每个点入度为1（因此每个环上点的子树，父亲指向儿子）

基环树的关键就是找到环，可以先把环当作这个无根树的 “根” ，也就是把环当成一个点（先不管它），这样一颗基环树就变成了一个普通的树，然后我们先按照解决普通树的方法对“根”的所有子树依次处理求解答案，最后在单独对环上所有的点进行操作求解最终答案即可。

[https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/1187830/nei-xiang-ji-huan-shu-tuo-bu-pai-xu-fen-c1i1b/](https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/1187830/nei-xiang-ji-huan-shu-tuo-bu-pai-xu-fen-c1i1b/)

## [有向图访问计数](https://leetcode.cn/contest/weekly-contest-365/problems/count-visited-nodes-in-a-directed-graph/)

内向基环树上每个点可以访问到的不同顶点个数。

```cpp
vector<int> countVisitedNodes(vector<int>& g) {
    int n = g.size();
    vector<int> in(n);
    vector<vector<int>> rg(n);
    for (int i = 0; i < n; i++) {
        int j = g[i];
        in[j]++, rg[j].push_back(i);
    }

    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    while (!q.empty()) {
        int x= q.front(), y = g[x]; q.pop();
        if (--in[y] == 0) q.push(y);
    }

    vector<int> ans(n);

    function<void(int, int)> rdfs = [&](int x, int depth) {
        ans[x] = depth;
        for (auto y : rg[x]) if (!in[y]) rdfs(y, depth + 1);
    };

    for (int i = 0; i < n; i++) {
        if (in[i] <= 0) continue;

        vector<int> ring;
        ring.push_back(i), in[i] =-1;
        for (int x = g[i]; x != i; x = g[x]) ring.push_back(x), in[x] = -1;

        for (auto x : ring) rdfs(x, ring.size());
    }
    return ans;
}
```
