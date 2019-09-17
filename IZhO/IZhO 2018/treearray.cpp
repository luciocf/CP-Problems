// IZhO 2018 - TreeArray
// Lúcio Cardoso

// Solution: Same as https://github.com/thecodingwizard/competitive-programming/blob/master/IZhO/IZhO%2018-treearray.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n, m, q;
int a[maxn];

set<int> st1[maxn], st2[maxn];

int nivel[maxn];

int tab[maxn][19];

vector<int> grafo[maxn];

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
	for (int j = 1; j < 19; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = 18; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = 18; i >= 0; i--)
		if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return tab[u][0];
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);
	build();

	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i]);

		st1[a[i]].insert(i);
		if (i > 1) st2[lca(a[i-1], a[i])].insert(i-1);
	}

	for (int i = 1; i <= q; i++)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int pos, v;
			scanf("%d %d", &pos, &v);

			st1[a[pos]].erase(pos);
			st1[v].insert(pos);

			if (pos > 1)
			{
				st2[lca(a[pos], a[pos-1])].erase(pos-1);
				st2[lca(v, a[pos-1])].insert(pos-1);
			}

			if (pos < m)
			{
				st2[lca(a[pos], a[pos+1])].erase(pos);
				st2[lca(v, a[pos+1])].insert(pos);
			}

			a[pos] = v;
		}
		else
		{
			int l, r, v;
			scanf("%d %d %d", &l, &r, &v);

			auto it = st1[v].lower_bound(l);

			if (it != st1[v].end() && *it <= r) printf("%d %d\n", *it, *it);
			else
			{
				it = st2[v].lower_bound(l);

				if (it != st2[v].end() && *it < r)
					printf("%d %d\n", *it, *it+1);
				else
					printf("-1 -1\n");
			}
		}
	}
}
