// Codeforces 592D - Super M
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

bool is[maxn];

int qtd[maxn], dp[2][maxn], mx[2][maxn];

int ans[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		if (is[v] || qtd[v])
		{
			qtd[u]++;
			dp[0][u] += 2+dp[0][v];

			if (dp[1][v]-dp[0][v]-1 < mx[0][u]) mx[1][u] = mx[0][u], mx[0][u] = dp[1][v]-dp[0][v]-1;
			else if (dp[1][v]-dp[0][v]-1 < mx[1][u]) mx[1][u] = dp[1][v]-dp[0][v]-1;
		}
	}

	if (qtd[u]) dp[1][u] = dp[0][u] + mx[0][u];
}

void solve(int u, int p)
{
	ans[u] = dp[1][u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		int ant[] = {qtd[u], dp[0][u], dp[1][u], mx[0][u], mx[1][u]};

		if (qtd[v] || is[v])
		{
			qtd[u]--, dp[0][u] -= (2+dp[0][v]);

			if (mx[0][u] == dp[1][v]-dp[0][v]-1) mx[0][u] = mx[1][u];
		}

		dp[1][u] = dp[0][u] + mx[0][u];

		if (qtd[u] || is[u])
		{	
			qtd[v]++, dp[0][v] += (2+dp[0][u]);

			if (dp[1][u]-dp[0][u]-1 < mx[0][v]) mx[1][v] = mx[0][v], mx[0][v] = dp[1][u]-dp[0][u]-1;
			else if (dp[1][u]-dp[0][u]-1 < mx[1][v]) mx[1][v] = dp[1][u]-dp[0][u]-1;
		}

		if (qtd[v]) dp[1][v] = dp[0][v] + mx[0][v];

		solve(v, u);

		qtd[u] = ant[0], dp[0][u] = ant[1], dp[1][u] = ant[2], mx[0][u] = ant[3], mx[1][u] = ant[4];
	}
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= m; i++)
	{
		int c;
		scanf("%d", &c);

		is[c] = 1;
	}


	dfs(1, 0);
	solve(1, 0);

	int tot = 1e9+10, ind = 1;
	for (int i = 1; i <= n; i++)
		if (tot > ans[i])
			tot = ans[i], ind = i;

	printf("%d\n%d\n", ind, tot);
}
