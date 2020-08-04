// Codeforces 980E - The Number Games
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int n;
bool mark[maxn];

vector<int> grafo[maxn];

struct BinaryLifting
{
	int nivel[maxn];
	int tab[maxn][20];

	void dfs(int u, int p)
	{
		for (auto v: grafo[u])
		{
			if (v == p) continue;

			tab[v][0] = u, nivel[v] = nivel[u]+1;
			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int j = 1; j < 20; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int get(int u)
	{
		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && !mark[tab[u][i]])
				u = tab[u][i];

		return u;
	}
} LCA;

void colore(int u)
{
	while (!mark[u])
	{
		mark[u] = 1;
		u = LCA.tab[u][0];
	}
}

int main(void)
{
	int k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	LCA.dfs(n, 0); LCA.build();

	int tot = 1;
	mark[n] = 1;

	for (int v = n-1; v >= 1; v--)
	{
		if (mark[v]) continue;

		int u = LCA.get(v);

		if (LCA.nivel[v]-LCA.nivel[u]+1+tot <= n-k)
		{
			colore(v);
			tot += LCA.nivel[v]-LCA.nivel[u]+1;
		}
	}

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			printf("%d ", i);
	printf("\n");
}
