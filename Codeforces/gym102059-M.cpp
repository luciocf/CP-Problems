// 2018-2019 XIX Open Cup, Grand Prix of Korea - M - Utilitarianism
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define int long long 

typedef long long ll;
typedef pair<ll,ll> pii;

const int maxn = 3e5+10;
const ll inf = 1e12;

int n, k;
ll add;
pii dp[maxn][2];

vector<pii> grafo[maxn];

void solve(int u, int p)
{
    ll soma = 0, tot = 0;

    for (auto pp: grafo[u])
    {
        int v = pp.ff, w = pp.ss;
        if (v == p) continue;

        solve(v, u);

        soma += dp[v][0].ff;
        tot += dp[v][0].ss;
    }

    dp[u][0] = dp[u][1] = {soma, tot};

    for (auto pp: grafo[u])
    {
        int v = pp.ff, w = pp.ss;
        if (v == p) continue;

        ll x = tot - dp[v][0].ss + dp[v][1].ss + 1;
        ll s = soma - dp[v][0].ff + dp[v][1].ff + 1ll*w + 1ll*add;

        if (s > dp[u][0].ff || (s == dp[u][0].ff && x > dp[u][0].ss))
            dp[u][0] = {s, x};
    }
}

pii check(void)
{
    memset(dp, 0, sizeof dp);

    solve(1, 0);

    return {dp[1][0].ss, dp[1][0].ff};
}

int32_t main()
{
    cin >> n >> k;

    for(int i = 1; i < n; i++)
    {
        int u, v, d;
        cin >> u >> v >> d;

        grafo[u].push_back({v, d});
        grafo[v].push_back({u, d});
    }

    ll ini = -inf, fim = inf, lastx = -1;
    pii ans = {-1, 0};

    while(ini <= fim)
    {
        ll mid = (ini + fim) >> 1;
        add = mid;

        if (check().ff < k) ini = mid + 1;
        else
        {
            fim = mid - 1, ans = check();
            lastx = mid;
        }
    }

    if (ans.ff == -1) cout << "Impossible\n";
    else cout << ans.ss - 1ll*k*lastx << "\n";
}
