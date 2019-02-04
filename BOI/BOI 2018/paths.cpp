// BOI 2018 - Paths
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;
const int MAXK = 6;

typedef long long ll;

int n, m, k, num[MAXN];

ll dp[MAXN][MAXK][1<<MAXK];

vector<int> grafo[MAXN];

ll solve(int u, int qtd, int mask)
{
    if (qtd == 1) return 1;
    if (dp[u][qtd][mask] != -1) return dp[u][qtd][mask];

    ll ans = 0LL;
    for (int i = 0; i < (int) grafo[u].size(); i++)
    {
        int v = grafo[u][i];
        int c = num[v];

        if (!(mask&(1<<c))) ans += solve(v, qtd-1, mask|(1<<c));
    }
    return dp[u][qtd][mask] = ans;
}

int main(void)
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) cin >> num[i];

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        grafo[a].push_back(b); grafo[b].push_back(a);
    }

    ll ans = 0LL;
    for (int l = 2; l <= k; l++)
    {
        memset(dp, -1, sizeof dp);
        for (int i = 0; i < n; i++) ans += solve(i, l, (1<<num[i]));
    }
    cout << ans << "\n";
}
