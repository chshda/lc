#include "bits/stdc++.h"
using namespace std;


class Solution {
public:
    vector<int> f(vector<int>& g) {
        int n = g.size();
        vector<int> in(n); // 入度
        vector<vector<int>> rg(n); // 反图
        for (int i = 0; i < n; i++) {
            int j = g[i];
            in[j]++, rg[j].push_back(i);
        }

        queue<int> q;
        for (int i = 0; i < n; i++) if (in[i] == 0) q.push(i);
        while(!q.empty()) {
            int x = q.front(), y = g[x]; q.pop();
            if (--in[y] == 0) q.push(y);
        }

        vector<int> ans(n);

        function<void(int, int)> rdfs = [&](int x, int depth) {
            ans[x] = depth;
            for (auto y : rg[x]) if (in[y] == 0) rdfs(y, depth+1);
        };

        for (int i = 0; i < n; i++) {
            if (in[i] <= 0) continue;

            vector<int> ring;
            for (int x = i; ; x = g[x]) {
                ring.push_back(x), in[x] = -1;
                if (g[x] == i) break;
            }

            for (auto x : ring) rdfs(x, ring.size());
        }        
        return ans;
    }
};


int main() {
#ifdef LOCAL_PROJECT
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    vector<string> msg{"123",  "C++",     "World",
                       "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg) {
        cout << word << " ";
    }
    cout << endl;
}

class Solution {
public:
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
}