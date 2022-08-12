#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 10, inf = 1e18;
int n, m;

// 题意: 最短 欧拉回路(保证存在)
// 左部点: 当前点   右部点: 下一跳点
// 如果找到完美匹配 两边都是全排列 每个数只出现一次, 出度入度都为1
// 1 - 5
// 5 - 4
// 2 - 3
// 4 - 2
// 3 - 1

// KM模板   带权二分图最大匹配
struct KM {     // KM max-weighted matching
    int matchb[N], vb[N], ka[N], kb[N], p[N], c[N], w[N][N], n;
    void bfs(int u)
    {
        int a, v = 0, vl = 0, d;
        for (int i = 1; i <= n; i++)    p[i] = 0, c[i] = inf;
        matchb[v] = u;
        do {
            a = matchb[v], d = inf, vb[v] = 1;
            for (int b = 1; b <= n; b++)
                if (!vb[b]) {
                    if (c[b] > ka[a] + kb[b] - w[a][b])
                        c[b] = ka[a] + kb[b] - w[a][b], p[b] = v;
                    if (c[b] < d)    d = c[b], vl = b;
                }
            for (int b = 0; b <= n; b++)
                if (vb[b])      ka[matchb[b]] -= d, kb[b] += d;
                else            c[b] -= d;
            v = vl;
        } while (matchb[v]);
        while (v)               matchb[v] = matchb[p[v]], v = p[v];
    }
    int solve()
    {
        for (int i = 1; i <= n; i++)    matchb[i] = ka[i] = kb[i] = 0;
        for (int a = 1; a <= n; a++)
            fill (vb, vb + 1 + n, 0),   bfs(a);
        int res = 0;
        for (int b = 1; b <= n; b++)    res += (w[matchb[b]][b] == -inf ? 0 : w[matchb[b]][b]);
        return res;
    }
};

void solve()
{
    KM km;
    cin >> n >> m;
    km.n = n;
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++j)
            km.w[i][j] = -inf;
    for(int i = 1; i <= m; ++ i)
    {
        int u, v, ww;       cin >> u >> v >> ww;
        km.w[u][v] = max(-ww, km.w[u][v]);
    }
    cout << -km.solve() << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    #ifdef LOCAL
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    #endif
    int tt; cin >> tt;
    while (tt--)        solve();
    return 0;
}