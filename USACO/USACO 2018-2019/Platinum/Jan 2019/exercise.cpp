// USACO 2018/2019 - Exercise Route
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxl = 20;

int n;

int nivel[maxn];

int tab[maxn][maxl];

ll val[maxn], soma[maxn];

vector<int> grafo[maxn];
vector<pii> edge;

map<pii, int> mp;

void dfs1(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, tab[v][0] = u;
		dfs1(v, u);
	}
}

void build(void)
{
	for (int j = 1; j < maxl; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = maxl-1; i >= 0; i--)
		if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return tab[u][0];
}

int last(int u, int v)
{
	if (u == v) return 0;

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u]-(1<<i) > nivel[v])
			u = tab[u][i];

	return u;
}

void pref(int u, int p, ll s)
{
	soma[u] = s;

	for (auto v: grafo[u])
		if (v != p)
			pref(v, u, s+val[v]);
}

int main(void)
{
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);

	int m;
	scanf("%d %d", &n, &m);

	m -= (n-1);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs1(1, 0); build();

	ll ans = 0;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		edge.push_back({u, v});

		int l = lca(u, v);

		int e1 = last(u, l);
		int e2 = last(v, l);
		if (e1 > e2) swap(e1, e2);

		if (e1)
		{
			val[e1]++;
			ans -= val[e1];
		}

		if (e2)
		{
			val[e2]++;
			ans -= val[e2];
		}

		if (e1 && e2)
		{
			ans -= 1ll*mp[{e1, e2}];
			mp[{e1, e2}]++;
		}
	}

	pref(1, 0, 0);

	for (int i = 0; i < m; i++)
		ans += 1ll*(soma[edge[i].first] + soma[edge[i].second] - 2ll*soma[lca(edge[i].first, edge[i].second)]);

	printf("%lld\n", ans);
}
