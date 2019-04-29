// BOI 2019 - Alpine Valley
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e5+10;
const int maxl = 20;
const long long inf = 2e18+10;

typedef long long ll;

typedef pair<int, int> pii;

int n, s, q, e;

int w[maxn];
int pai[maxn], nivel[maxn];

ll dist[maxn], sub[maxn];

pair<int, ll> tab[maxn][maxl];

bool shop[maxn];

pii edge[maxn];

vector<pii> grafo[maxn];

void dfs(int u, int p)
{
	if (shop[u]) sub[u] = 0;

	for (auto pp: grafo[u])
	{
		int v = pp.first, d = w[pp.second];
		if (v == p) continue;

		pai[v] = u, nivel[v] = nivel[u]+1;
		dist[v] = dist[u]+1ll*d;

		dfs(v, u);

		sub[u] = min(sub[u], sub[v]+1ll*d);
	}
}

void build(void)
{
	for (int i = 1; i <= n; i++)
	{
		tab[i][0].ff = pai[i];
		tab[i][0].ss = inf;

		if (sub[i] != inf) tab[i][0].ss = min(tab[i][0].ss, sub[i]-dist[i]);
		if (sub[pai[i]] != inf) tab[i][0].ss = min(tab[i][0].ss, sub[pai[i]]-dist[pai[i]]);
	}

	for (int j = 1; j < maxl; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			tab[i][j].ff = tab[tab[i][j-1].ff][j-1].ff;
			tab[i][j].ss = min(tab[i][j-1].ss, tab[tab[i][j-1].ff][j-1].ss);
		}
	}
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u] - (1<<i) >= nivel[v])
			u = tab[u][i].ff;

	if (u == v) return u;

	for (int i = maxl-1; i >= 0; i--)
		if (tab[u][i].ff && tab[v][i].ff && tab[u][i].ff != tab[v][i].ff)
			u = tab[u][i].ff, v = tab[v][i].ff;

	return pai[u];
}

ll get(int u, int v)
{
	ll ans = (sub[u] == inf ? inf : sub[u]-dist[u]);

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u] - (1<<i) >= nivel[v])
			ans = min(ans, tab[u][i].ss), u = tab[u][i].ff;

	return ans;
}

int main(void)
{
	scanf("%d %d %d %d", &n, &s, &q, &e);

	for (int i = 1; i < n; i++)
	{
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);

		w[i] = c, edge[i] = {u, v};
		grafo[u].push_back({v, i}); grafo[v].push_back({u, i});
	}

	for (int i = 1; i <= s; i++)
	{
		int c;
		scanf("%d", &c);
		shop[c] = 1;
	}

	for (int i = 1; i <= n; i++)
		sub[i] = inf;

	dfs(e, 0); build();

	for (int i = 1; i <= q; i++)
	{
		int u, r;
		scanf("%d %d", &r, &u);

		int a = edge[r].first, b = edge[r].second;

		if (nivel[a] > nivel[b]) swap(a, b);

		if (lca(u, b) != b) printf("escaped\n");
		else
		{
			ll ans = get(u, b);

			if (ans == inf) printf("oo\n");
			else printf("%lld\n", ans+dist[u]);
		}
	}
}
