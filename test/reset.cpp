#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL_PROJECT
#define debug(x) cerr << #x << ": " << x << endl
#else
#define debug(...) 42
#endif

using ll = long long;
using pii = pair<int, int>;

void solve(int tc) {
    cout << "hello world!" << endl;
}

int32_t main() {
#ifdef LOCAL_PROJECT
    freopen("data/in.txt", "r", stdin);
    freopen("data/out.txt", "w", stdout);
    freopen("data/error.txt", "w", stderr);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    int tcn;
    cin >> tcn;
    for (int tc = 1; tc <= tcn; tc++) { debug(tc); solve(tc); }

    return 0;
}
