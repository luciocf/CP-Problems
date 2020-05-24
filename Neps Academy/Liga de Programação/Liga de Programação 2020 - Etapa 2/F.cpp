// Neps Academy - Liga de Programação 2020 - Etapa 2 - Árvore Colorida
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int a[maxn];

int bit[55][maxn];

int nivel[maxn];
int st[maxn], en[maxn], tt;

int tab[maxn][20];

vector<int> grafo[maxn];

void upd(int x, int v, int k)
{
	for (; x < maxn; x += (x&-x))
		bit[k][x] += v;
}

int soma(int x, int k)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[k][x];
	return ans;
}

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
	{
		if (v != p)
		{
			tab[v][0] = u;
			nivel[v] = nivel[u]+1;

			dfs(v, u);
		}
	}

	en[u] = ++tt;
}

void build(void)
{
	for (int j = 1; j <= 18; j++)
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
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0); build();

	for (int i = 1; i <= n; i++)
	{
		upd(st[i], 1, a[i]);
		upd(en[i], -1, a[i]);
	}

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int u, x;
			scanf("%d %d", &u, &x);

			upd(st[u], -1, a[u]);
			upd(en[u], 1, a[u]);

			a[u] = x;

			upd(st[u], 1, a[u]);
			upd(en[u], -1, a[u]);
		}
		else
		{
			int u, v;
			scanf("%d %d", &u, &v);

			int l = lca(u, v);

			int ans = 0;
			for (int i = 1; i <= 50; i++)
				if (soma(st[u], i) + soma(st[v], i) - 2*soma(st[l], i) + (a[l] == i))
					ans++;

			printf("%d\n", ans);
		}
	}
}
