// COCI 2008-2009 - Najkraci
// Lúcio Cardoso

// Solution:
// 1. For each vertex S, run dijkstra's with S as source and build the graph formed by the edges
//    belonging to any shortest path. This graph will be a DAG.

// 2. For every vertex u, Use DP to calculate the amount of paths from starting from S that reach u. Call this
//    in[u]. Then, also calculate the amount of paths that leave u and reach some other vertex. Call this out[u].
//    (When calculating in[u], we take the vertices u in the topological sorting of the DAG, and when calculating out[u], we take
//    them in reverse topo. sort.)

// 3. The answer to every edge (u->v) for a fixed S is in[u]*out[v], if the edge (u->v) is in the DAG. The answer for each edge
//    is the sum of this product for every fixed S.

// Complexity: O(N*M * log N)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;
const int inf = 1e9+10;
const int mod = 1e9+7;

typedef pair<int, int> pii;
typedef long long ll;

int n, m;

int dist[maxn];
int in[maxn], out[maxn], ans[maxn];

bool mark[maxn];

vector<pair<pii, int>> grafo[maxn];
vector<pii> dag[maxn];

vector<int> ord;

void init(void)
{
	memset(mark, 0, sizeof mark);
	memset(in, 0, sizeof in);
	memset(out, 0, sizeof out);

	ord.clear();
	for (int i = 1; i <= n; i++)
		dag[i].clear();
}

void dijkstra(int s)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii> > fila;

	dist[s] = 0, fila.push({0, s});

	while (!fila.empty())
	{
		int u = fila.top().second;
		fila.pop();

		if (mark[u]) continue;

		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first.first, d = pp.first.second;

			if (dist[v] > dist[u]+d)
			{
				dist[v] = dist[u]+d;
				fila.push({dist[v], v});
			}
		}
	}
}

void build(void)
{
	for (int u = 1; u <= n; u++)
	{
		for (auto pp: grafo[u])
		{
			int v = pp.first.first, d = pp.first.second;
			int e = pp.second;

			if (dist[u]+d == dist[v])
				dag[u].push_back({v, e});
		}
	}
}

void dfs(int u)
{
	mark[u] = 1;
	for (auto v: dag[u])
		if (!mark[v.first])
			dfs(v.first);

	ord.push_back(u);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({{v, w}, i});
	}

	for (int s = 1; s <= n; s++)
	{
		init();

		dijkstra(s); build();

		memset(mark, 0, sizeof mark);
		dfs(s);

		for (auto i: ord)
		{
			out[i] = 1;
			for (auto v: dag[i])
				out[i] = (out[i]+out[v.first])%mod;
		}

		reverse(ord.begin(), ord.end());

		in[s] = 1;
		for (auto i: ord)
			for (auto v: dag[i])
				in[v.first] = (in[v.first]+in[i])%mod;

		for (int u = 1; u <= n; u++)
			for (auto v: dag[u])
				ans[v.second] = (ans[v.second] + (1ll*in[u]*out[v.first])%mod)%mod;
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
