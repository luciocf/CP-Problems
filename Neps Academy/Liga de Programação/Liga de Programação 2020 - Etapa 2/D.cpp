// Neps Academy - Liga de Programação 2020 - Etapa 2 - Compressão de Rotas
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int n, r;

int nivel[maxn];
int tab[maxn][20];

vector<int> grafo[maxn];
vector<int> path[maxn];

int pos[maxn][maxn];
int dp[maxn];

vector<int> inside[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			tab[v][0] = u, nivel[v] = nivel[u]+1;
			dfs(v, u);
		}
	}
}

void build(void)
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

void get_path(int u, int v, int ind)
{
	int l = lca(u, v);

	vector<int> path1, path2;

	while (u != l)
	{
		path1.push_back(u);
		u = tab[u][0];
	}

	while (v != l)
	{
		path2.push_back(v);
		v = tab[v][0];
	}

	reverse(path2.begin(), path2.end());

	for (auto x: path1)
		path[ind].push_back(x);

	path[ind].push_back(l);

	for (auto x: path2)
		path[ind].push_back(x);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0); build();

	scanf("%d", &r);

	for (int i = 1; i <= r; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		get_path(u, v, i);

		for (int j = 0; j < path[i].size(); j++)
			pos[i][path[i][j]] = j+1;
	}	

	int ans = 0;

	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= n; j++)
			inside[j].clear();

		for (int j = 1; j <= r; j++)
		{
			if (j == i) continue;

			int a = path[j][0], b = path[j].back();

			if (pos[i][a] && pos[i][b] && pos[i][a] < pos[i][b])
			{
				if (pos[i][b] >= path[i].size())
					inside[a].push_back(0);
				else
					inside[a].push_back(path[i][pos[i][b]]);
			}
		}

		memset(dp, 0, sizeof dp);

		dp[path[i].back()] = 1;

		for (int j = (int)path[i].size()-2; j >= 0; j--)
		{
			int u = path[i][j];

			dp[u] = 1 + dp[path[i][j+1]];

			for (auto v: inside[u])
				dp[u] = min(dp[u], 1 + dp[v]);
		}

		ans += dp[path[i][0]];
	}

	printf("%d\n", ans);
}
