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

## [参加会议的最多员工数](https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/description/)

一个公司准备组织一场会议，邀请名单上有 n 位员工。公司准备了一张圆形的桌子，可以坐下任意数目的员工。每位员工都有一位喜欢的员工，每位员工当且仅当他被安排在喜欢员工的旁边，他才会参加会议。每位员工喜欢的员工不会是他自己。请你返回参加会议的 最多员工数目 。

基环大小大于 2 的情况

* 基环上的节点组成了一个环，因而可以组成一个圆桌
* 树枝上的点，若插入圆桌上两人中间，会导致节点无法和其喜欢的员工坐在一起，因此树枝上的点是无法插入圆桌的
* 树枝上的点也不能单独组成圆桌，因为这样会存在一个出度为 0 的节点，其无法和其喜欢的员工坐在一起。
* 因此，对于基环大小大于 222 的情况，圆桌的最大员工数目即为最大的基环大小，

基环大小等于 2 的情况，比如

```
5 -> 4 -> 2 -> 0 <-> 1 <-6
     3 -> ^
```

* 我们可以先让 0 和 1 坐在圆桌旁（假设 0 坐在 1 左侧），那么 0 这一侧的树枝只能坐在 0 的左侧，而 1 这一侧的树枝只能坐在 1 的右侧。
* 2 可以紧靠着坐在 0 的左侧，而 3 和 4 只能选一个坐在 2 的左侧（如果 4 紧靠着坐在 2 的左侧，那么 3 是无法紧靠着坐在 444 的左侧的，反之亦然）。这意味着从 0 出发倒着找树枝上的点（反图），每个点只能在其反图上选择其中一个子节点，因此 0 这一侧的节点必须组成一条链，那么我们可以找最长的那条链。
* 对于 1 这一侧同理。将这两条最长链拼起来即为该基环树能组成的圆桌的最大员工数。
* 对于多个基环大小等于 2 的基环树，每个基环树所对应的链，都可以拼在其余链的末尾，因此我们可以将这些链全部拼成一个圆桌。

```cpp
int maximumInvitations(vector<int>& g) {
    int n = g.size();
    vector<int> in(n), mx_depth(n);
    for (auto i : g) in[i]++;

    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    while (!q.empty()) {
        int x = q.front(), y = g[x]; q.pop();
        mx_depth[x]++;
        mx_depth[y] = max(mx_depth[y], mx_depth[x] + 1);
        if (--in[y] == 0) q.push(y);
    }

    int max_ring = 0, sum_chain = 0;
    for (int i = 0; i < n; i++) {
        if (in[i] <= 0) continue;
        in[i] = -1;

        int ring_size = 1;
        for (int x = g[i]; x != i; x = g[x]) ring_size++, in[x] = -1;

        if (ring_size == 2) sum_chain += mx_depth[i] + mx_depth[g[i]] + 2;
        else max_ring = max(max_ring, ring_size);
    }
    return max(max_ring, sum_chain);
}
```