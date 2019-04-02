// CEOI 2017 - One-Way Streets
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxl = 20;
const int inf = 1e9+10;

typedef pair<int, int> pii;

int n, m;

int in[maxn], low[maxn], tt;
int comp[maxn], bcc;

int pai[maxn], nivel[maxn];

int tab[maxn][maxl];

int menor[2][maxn];

int ans[maxn];

bool bridge[maxn], mark[maxn];

vector<pair<int, pii>> grafo[maxn], tree[maxn];

void find_bridge(int u, int ant)
{
	in[u] = low[u] = ++tt;

	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second.first;

		if (e == ant) continue;

		if (in[v])
		{
			low[u] = min(low[u], in[v]);
			continue;
		}

		find_bridge(v, e);

		if (low[v] > in[u]) bridge[e] = true;

		low[u] = min(low[u], low[v]);
	}
}

void fill(int u, int cc)
{
	comp[u] = cc;

	for (auto v: grafo[u])
		if (!comp[v.first] && !bridge[v.second.first])
			fill(v.first, cc);
}

void dfs(int u, int p)
{
	mark[u] = true;
	menor[0][u] = menor[1][u] = inf;

	for (auto pp: tree[u])
	{
		int v = pp.first, e = pp.second.first;
		if (v == p) continue;

		nivel[v] = nivel[u]+1, pai[v] = u;

		dfs(v, u);
	}
}

void build(void)
{
	for (int i = 1; i <= n; i++)
		tab[i][0] = pai[i];

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

	return pai[u];
}

int solve_up(int u, int p)
{
	int m = inf;
	mark[u] = true;

	for (auto pp: tree[u])
	{
		int v = pp.first, e = pp.second.first;
		int direct = pp.second.second;

		if (v == p) continue;

		int x = solve_up(v, u);

		if (x <= nivel[u])
		{
			if (direct) ans[e] = 0;
			else ans[e] = 1;
		}

		m = min(m, x);
	}

	return min(m, menor[1][u]);
}

int solve_down(int u, int p)
{
	int m = inf;
	mark[u] = true;

	for (auto pp: tree[u])
	{
		int v = pp.first, e = pp.second.first;
		int direct = pp.second.second;

		if (v == p) continue;

		int x = solve_down(v, u);

		if (x <= nivel[u])
		{
			if (direct) ans[e] = 1;
			else ans[e] = 0;
		}

		m = min(m, x);
	}

	return min(m, menor[0][u]);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		if (u != v)
		{
			grafo[u].push_back({v, {i, 1}});
			grafo[v].push_back({u, {i, 0}});
		}

		ans[i] = 2;
	}

	for (int i = 1; i <= n; i++)
		if (!in[i])
			find_bridge(i, 0);

	for (int i = 1; i <= n; i++)
		if (!comp[i])
			fill(i, ++bcc);

	for (int i = 1; i <= n; i++)
	{
		for (auto pp: grafo[i])
		{
			int v = pp.first, e = pp.second.first;
			int direct = pp.second.second;

			if (bridge[e]) 
				tree[comp[i]].push_back({comp[v], {e, direct}});
		}
	}

	for (int i = 1; i <= bcc; i++)
		if (!mark[i])
			dfs(i, 0);

	build();

	int p;
	scanf("%d", &p);

	for (int i = 1; i <= p; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		u = comp[u], v = comp[v];
		
		int low = lca(u, v);

		menor[1][u] = min(menor[1][u], nivel[low]);
		menor[0][v] = min(menor[0][v], nivel[low]);
	}

	memset(mark, 0, sizeof mark);
	for (int i = 1; i <= bcc; i++)
		if (!mark[i])
			solve_up(i, 0);

	memset(mark, 0, sizeof mark);
	for (int i = 1; i <= bcc; i++)
		if (!mark[i])
			solve_down(i, 0);

	for (int i = 1; i <= m; i++)
	{
		if (ans[i] == 2) printf("B");
		else if (ans[i] == 1) printf("R");
		else printf("L");
	}

	printf("\n");
}
