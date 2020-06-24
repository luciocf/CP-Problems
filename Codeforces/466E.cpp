// Codeforces 466E - Information Graph
// Lúcio Cardoso

// Solution is pretty much the same as in editorial, except I add weights to the edges in the graph. The weight
// in a edge (u -> v) is the "time" in which this edge was added (i.e the index of this '1' operation). The query
// then reduces to checking if the maximum edge in the path from v -> u is smaller than or equal to the last edge index
// added before the document was sent.

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxl = 20;

struct DSU
{
	int pai[maxn], peso[maxn];

	DSU(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
	}
};

int n, m;

int pai[maxn], nivel[maxn];

int tab[maxn][maxl], mx[maxn][maxl];

int event[maxn], tempo[maxn];

vector<pii> grafo[maxn];

void dfs(int u, int p)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p) continue;

		tab[v][0] = u, mx[v][0] = w, nivel[v] = nivel[u]+1;
		dfs(v, u);
	}
}

void build(void)
{
	for (int j = 1; j < maxl; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			tab[i][j] = tab[tab[i][j-1]][j-1];
			mx[i][j] = max(mx[i][j-1], mx[tab[i][j-1]][j-1]);
		}
	}
}

int get_mx(int u, int v)
{
	int ans = 0;

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			ans = max(ans, mx[u][i]), u = tab[u][i];

	return ans;
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

int main(void)
{
	scanf("%d %d", &n, &m);

	DSU dsu(n);

	int qtd_edge = 0, qtd_ev = 0;

	vector<pii> qry;

	while (m--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			++qtd_edge;

			pai[u] = v;
			grafo[u].push_back({v, qtd_edge}); grafo[v].push_back({u, qtd_edge});

			dsu.Join(u, v);
		}
		else if (op == 2)
		{
			int u;
			scanf("%d", &u);

			tempo[++qtd_ev] = qtd_edge;
			event[qtd_ev] = u;
		}
		else
		{
			int u, ind;
			scanf("%d %d", &u, &ind);

			qry.push_back({u, ind});
		}
	}

	for (int i = 1; i <= n; i++)
		if (pai[i] == 0)
			dfs(i, 0);

	build();

	for (auto pp: qry)
	{
		int u = pp.first, ind = pp.second;
		int v = event[ind];

		if (dsu.Find(u) != dsu.Find(v))
		{
			printf("NO\n");
			continue;
		}

		int l = lca(u, v);

		if (l != u) printf("NO\n");
		else if (get_mx(v, u) <= tempo[ind]) printf("YES\n");
		else printf("NO\n");
	}
}
