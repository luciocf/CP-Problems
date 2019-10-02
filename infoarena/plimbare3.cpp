// infoarena - Plimbare 3
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int d[3][maxn], diam[2][maxn], maior[maxn];

int ans[maxn];

vector<pii> grafo[maxn];

void dfs1(int u, int p)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first;
		if (v == p) continue;

		dfs1(v, u);

		if (maior[v] > diam[0][u])
			diam[1][u] = diam[0][u], diam[0][u] = maior[v];
		else if (maior[v] > diam[1][u])
			diam[1][u] = maior[v];

		if (d[0][v]+1 > d[0][u])
			d[2][u] = d[1][u], d[1][u] = d[0][u], d[0][u] = d[0][v]+1;
		else if (d[0][v]+1 > d[1][u])
			d[2][u] = d[1][u], d[1][u] = d[0][v]+1;
		else if (d[0][v]+1 > d[2][u])
			d[2][u] = d[0][v]+1;
	}

	maior[u] = max(diam[0][u], d[0][u]+d[1][u]);
}

void solve(int u, int p)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;
		if (v == p) continue;

		int ant[4] = {d[0][u], d[1][u], diam[0][u], maior[u]};

		if (d[0][v]+1 == d[0][u])
		{
			d[0][u] = d[1][u];
			d[1][u] = d[2][u];
		}
		else if (d[0][v]+1 == d[1][u])
		{
			d[1][u] = d[2][u];
		}

		if (diam[0][u] == maior[v])
			diam[0][u] = diam[1][u];

		maior[u] = max(diam[0][u], d[0][u]+d[1][u]);

		ans[e] = maior[v]+maior[u]+1;

		if (maior[u] > diam[0][v])
			diam[1][v] = diam[0][v], diam[0][v] = maior[u];
		else if (maior[u] > diam[1][v])
			diam[1][v] = maior[u];

		if (d[0][u]+1 > d[0][v])
			d[2][v] = d[1][v], d[1][v] = d[0][v], d[0][v] = d[0][u]+1;
		else if (d[0][u]+1 > d[1][v])
			d[2][v] = d[1][v], d[1][v] = d[0][u]+1;
		else if (d[0][u]+1 > d[2][v])
			d[2][v] = d[0][u]+1;

		maior[v] = max(diam[0][v], d[0][v]+d[1][v]);

		solve(v, u);

		d[0][u] = ant[0], d[1][u] = ant[1], diam[0][u] = ant[2], maior[u] = ant[3];
	}
}

int main(void)
{
	freopen("plimbare3.in", "r", stdin);
	freopen("plimbare3.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});
	}

	dfs1(1, 0);
	solve(1, 0);

	for (int i = 1; i < n; i++)
		printf("%d\n", ans[i]);
}
