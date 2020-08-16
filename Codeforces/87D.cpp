// Codeforces 87D - Beautiful Road
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e5+10;

ll ans[maxn];

struct Edge
{
	int u, v, w, ind;
} edge[maxn];

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(int n)
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
} dsu;

struct CompressedGraph
{
	vector<int> grafo[maxn];
	int pai[maxn], sub[maxn];
	int comp[maxn], tot[maxn];

	void init(vector<Edge> &V)
	{
		for (auto pp: V)
		{
			grafo[pp.u].push_back(pp.v);
			grafo[pp.v].push_back(pp.u);
		}
	}

	void clear(vector<Edge> &V)
	{
		for (auto pp: V)
		{
			sub[pp.u] = sub[pp.v] = tot[comp[pp.u]] = 0;
			comp[pp.u] = comp[pp.v] = 0;

			grafo[pp.u].clear(); grafo[pp.v].clear();
		}
	}

	void dfs(int u, int cc)
	{
		sub[u] = dsu.peso[u], comp[u] = cc;

		for (auto v: grafo[u])
		{
			if (comp[v]) continue;

			pai[v] = u;

			dfs(v, cc);

			sub[u] += sub[v];
		}

		tot[cc] = sub[u];
	}	
} G;

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
		edge[i].ind = i;
	}

	dsu.init(n);

	sort(edge+1, edge+n, [&] (Edge a, Edge b) {return a.w < b.w;});

	for (int i = 1; i < n; i++)
	{
		vector<Edge> E;

		int j;
		for (j = i; j < n && edge[j].w == edge[i].w; j++)
			E.push_back({dsu.Find(edge[j].u), dsu.Find(edge[j].v), -1, edge[j].ind});
		j--;

		G.init(E);

		int cc = 0;

		for (auto e: E)
			if (!G.comp[e.u])
				G.dfs(e.u, ++cc);

		for (auto e: E)
		{
			int u = e.u, v = e.v;
			if (G.pai[u] == v) swap(u, v);

			ans[e.ind] += 1ll*G.sub[v]*(G.tot[G.comp[v]]-G.sub[v]);
		}

		G.clear(E);

		for (auto e: E)
			dsu.Join(e.u, e.v);
		i = j;
	}

	ll mx = 0;
	for (int i = 1; i < n; i++)
		mx = max(mx, 2ll*ans[i]);

	vector<int> final;

	for (int i = 1; i < n; i++)
		if (2ll*ans[i] == mx)
			final.push_back(i);

	printf("%lld %d\n", mx, (int)final.size());
	for (auto i: final)
		printf("%d ", i);
	printf("\n");
}
