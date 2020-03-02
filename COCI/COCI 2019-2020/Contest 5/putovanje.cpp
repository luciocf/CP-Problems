// COCI 2019/2020 - Putovanje
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int n;
ll ans;

int tab[maxn][20], nivel[maxn];

int val[maxn];

vector<int> grafo[maxn];
map<pii, int> c1, c2;

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			nivel[v] = nivel[u]+1, tab[v][0] = u;
			dfs(v, u);
		}
	}
}

void build(void)
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = 19; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = 19; i >= 0; i--)
		if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return tab[u][0];
}

int solve(int u, int p)
{
	int tot = val[u];

	for (auto v: grafo[u])
		if (v != p)
			tot += solve(v, u);

	if (u != 1)
	{
		if (1ll*tot*c1[{u, p}] > c2[{u, p}])
			ans += 1ll*c2[{u, p}];
		else
			ans += 1ll*tot*c1[{u, p}];
	}

	return tot;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v, a, b;
		scanf("%d %d %d %d", &u, &v, &a, &b);

		grafo[u].push_back(v), grafo[v].push_back(u);
		c1[{u, v}] = c1[{v, u}] = a, c2[{u, v}] = c2[{v, u}] = b;
	}

	dfs(1, 0); build();

	for (int i = 1; i < n; i++)
	{
		val[i]++, val[i+1]++;
		val[lca(i, i+1)] -= 2;
	}

	solve(1, 0);

	printf("%lld\n", ans);
}
