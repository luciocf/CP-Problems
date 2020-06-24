// Codeforces 76A - Gift
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 5e4+10;
const ll inf = 2e18+10;

struct Edge
{
	int u, v, g, s, ind;
} edge[maxn];

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

int pai[maxn], edge_pai[maxn];

vector<pii> grafo[maxn];

bool comp(Edge a, Edge b) {return a.g < b.g;}

void dfs(int u, int p)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first, ind = pp.second;
		if (v == p) continue;

		pai[v] = u, edge_pai[v] = ind;
		dfs(v, u);
	}
}

Edge get_mx(int v)
{
	Edge ans = {-1, -1, -1, -1, -1};

	while (pai[v])
	{
		if (edge[edge_pai[v]].s > ans.s)
			ans = edge[edge_pai[v]];

		v = pai[v];
	}

	return ans;
}

int main(void)
{	
	int G, S;
	scanf("%d %d %d %d", &n, &m, &G, &S);

	DSU dsu(n);

	for (int i = 1; i <= m; i++)
	{
		int u, v, g, s;
		scanf("%d %d %d %d", &u, &v, &g, &s);

		edge[i] = {u, v, g, s, i};
	}

	sort(edge+1, edge+m+1, comp);

	for (int i = 1; i <= m; i++)
		edge[i] = {edge[i].u, edge[i].v, edge[i].g, edge[i].s, i};

	ll ans = inf;
	vector<Edge> V;

	int cc = n;
	int mx1 = 0, mx2 = 0;

	for (int i = 1; i <= m; i++)
	{
		int u = edge[i].u, v = edge[i].v;

		if (u == v) continue;

		if (dsu.Find(u) != dsu.Find(v))
		{
			dsu.Join(u, v);

			V.push_back(edge[i]);
			--cc;

			mx1 = max(mx1, edge[i].g);
			mx2 = max(mx2, edge[i].s);
		}
		else
		{
			for (int j = 1; j <= n; j++)
				grafo[j].clear();

			for (auto E: V)
			{
				grafo[E.u].push_back({E.v, E.ind});
				grafo[E.v].push_back({E.u, E.ind});
			}

			pai[u] = 0;
			dfs(u, 0);

			Edge mx = get_mx(v);

			if (mx.s <= edge[i].s) continue;

			mx1 = 0, mx2 = 0;

			vector<Edge> aux;

			aux.push_back(edge[i]);

			mx1 = max(mx1, edge[i].g);
			mx2 = max(mx2, edge[i].s);

			for (auto E: V)
			{
				if (E.ind == mx.ind) continue;

				aux.push_back(E);

				mx1 = max(mx1, E.g);
				mx2 = max(mx2, E.s);
			}

			swap(aux, V);
			aux.clear();
		}

		if (cc == 1)
			ans = min(ans, 1ll*mx1*G + 1ll*mx2*S);
	}

	if (ans == inf) printf("-1\n");
	else printf("%lld\n", ans);
}
