// Codeforces 1304E - 1-Trees and Queries
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxl = 20;

int n;

int st[maxn], en[maxn], tt;
int nivel[maxn], tab[maxn][maxl];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, tab[v][0] = u;
		dfs(v, u);
	}

	en[u] = tt;
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

int dist(int u, int v)
{
	return nivel[u]+nivel[v]-2*nivel[lca(u, v)];
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

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int a, b, u, v, k;
		scanf("%d %d %d %d %d", &a, &b, &u, &v, &k);

		int l = lca(a, b), c1, c2;
		int ciclo = dist(a, b)+1;

		if (st[u] < st[l] || en[u] > en[l]) c1 = l;
		else
		{
			if (dist(u, lca(u, a)) < dist(u, lca(u, b))) c1 = lca(u, a);
			else c1 = lca(u, b);
		}

		if (st[v] < st[l] || en[v] > en[l]) c2 = l;
		else
		{
			if (dist(v, lca(v, a)) < dist(v, lca(v, b))) c2 = lca(v, a);
			else c2 = lca(v, b);
		}

		int D1 = dist(u, c1)+dist(c1, c2)+dist(c2, v);
		int D2 = dist(u, c1)+(ciclo-dist(c1, c2))+dist(c2, v);

		if (min({dist(u, v), D1, D2}) > k)
		{
			printf("NO\n");
			continue;
		}

		if (dist(u, v) <= k && dist(u, v)%2 == k%2)
		{
			printf("YES\n");
			continue;
		}
		if ((D1 <= k && D1%2 == k%2) || (D2 <= k && D2%2 == k%2))
		{
			printf("YES\n");
			continue;
		}

		if ((ciclo+D1 <= k && (ciclo+D1)%2 == k%2) || (ciclo+D2 <= k && (ciclo+D2)%2 == k%2))
			printf("YES\n");
		else
			printf("NO\n");
	}
}
