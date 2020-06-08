// Infoarena - Maxdist
// Lúcio Cardoso

// Solution: https://github.com/thecodingwizard/competitive-programming/blob/master/Infoarena/maxdist.cpp

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int query[maxn];
bool out[maxn];

int ans1[maxn], ans2[maxn];

int nivel[maxn];

int tab[maxn][20];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		tab[v][0] = u;

		dfs(v, u);
	}
}

void build(int n)
{
	for (int j = 1; j <= 19; j++)
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

int dist(int u, int v)
{
	if (u == -1 || v == -1) return 0;

	return nivel[u]+nivel[v]-2*nivel[lca(u, v)];
}

void get_best(pii& pp, int u)
{
	if (pp.first == -1) pp.first = u;
	else if (pp.second == -1) pp.second = u;
	else
	{
		int d = dist(pp.first, pp.second);
		int d1 = dist(pp.first, u);
		int d2 = dist(pp.second, u);

		if (max({d, d1, d2}) == d1) pp.second = u;
		else if (max({d, d1, d2}) == d2) pp.first = u;
	}
}

int main(void)
{
	freopen("maxdist.in", "r", stdin); freopen("maxdist.out", "w", stdout);

	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0); build(n);

	pii pp = {-1, -1};

	for (int i = 1; i <= q; i++)
	{
		scanf("%d", &query[i]);
		out[query[i]] = true;

		get_best(pp, query[i]);

		ans2[i] = dist(pp.first, pp.second);
	}

	pp = {-1, -1};

	for (int i = 1; i <= n; i++)
		if (!out[i])
			get_best(pp, i);

	ans1[q] = dist(pp.first, pp.second);

	for (int i = q; i >= 2; i--)
	{
		get_best(pp, query[i]);
		ans1[i-1] = dist(pp.first, pp.second);
	}

	for (int i = 1; i <= q; i++)
		printf("%d %d\n", ans1[i], ans2[i]);
}
