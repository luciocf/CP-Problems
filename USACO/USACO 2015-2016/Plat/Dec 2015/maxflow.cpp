// USACO Platinum Dec 2015 - Max Flow
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10;
const int maxl = 20;

int n, k;

int nivel[maxn], pai[maxn];
int tab[maxn][maxl];

int tot[maxn], ans[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pai[v] = u, nivel[v] = nivel[u]+1;
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

int solve(int u, int p)
{
	ans[u] = tot[u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		solve(v, u);
		ans[u] += ans[v];
	}
}

int main(void)
{
	FILE *fin = fopen("maxflow.in", "r");
	FILE *fout = fopen("maxflow.out", "w");

	fscanf(fin, "%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(1, 0); build();

	for (int i = 1; i <= k; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		int l = lca(u, v);

		tot[u]++, tot[v]++;
		tot[l]--, tot[pai[l]]--;
	}

	solve(1, 0);

	int resp = 0;
	for (int i = 1; i <= n; i++)
		resp = max(resp, ans[i]);

	fprintf(fout, "%d\n", resp);
}
