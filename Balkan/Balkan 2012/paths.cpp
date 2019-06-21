// Balkan OI 2012 - Shortest Paths
// Lúcio Cardoso

// Solution:

// 1. Take the SP Tree (call it T) from the graph with A as root, and make sure the
// given path is present in the tree.

// 2. Suppose we've taken the edge (U, V) from the given path and removed it from T. It's
// not hard to prove that the shortest distance (not necessarily using only edges from T) 
// from B to any vertex K on the subtree of V can be achieved without crossing the edge (U, V).

// 3. Now, notice that when removing the edge (U, V) from T, the shortest path from A to B
// can be decomposed in the following way: dist(A, K1) + dist(K1, K2) + dist(K2, B), where K1
// is not in the subtree of V and K2 is necessarily in the subtree of V. We can find the minimum
// value for the above expression using multisets, and keep track of which vertices are allowed
// for being K1 and K2 using a dfs for each edge that is removed.

// Overall complexity is O(n^2 * log n).

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 2e3+10;
const long long inf = 2e18;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, s, t, k;

ll dist[maxn], dist2[maxn];
int pai[maxn];

int paiPath[maxn], son[maxn];

bool mark[maxn], inPath[maxn], ok[maxn];

vector<pii> grafo[maxn];
vector<int> tree[maxn], path;

multiset<ll> Val[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;
	dist[s] = 0;

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> fila;
	fila.push({0ll, s});

	while (!fila.empty())
	{
		int u = fila.top().ss;
		fila.pop();

		if (mark[u])
			continue;

		mark[u] = true;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist[v] > dist[u]+1ll*w)
			{
				dist[v] = dist[u]+1ll*w, pai[v] = u;
				fila.push({dist[v], v});
			}
			else if (dist[v] == dist[u]+1ll*w && u == paiPath[v])
				pai[v] = u;
		}
	}
}

void dijkstra2(void)
{
	for (int i = 1; i <= n; i++)
		dist2[i] = inf;
	dist2[t] = 0;

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> fila;
	fila.push({0ll, t});

	while (!fila.empty())
	{
		int u = fila.top().ss;
		fila.pop();

		if (mark[u])
			continue;

		mark[u] = true;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist2[v] > dist2[u]+1ll*w)
			{
				dist2[v] = dist2[u]+1ll*w;
				fila.push({dist2[v], v});
			}
		}
	}
}

void add(int u)
{
	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;

		if (inPath[v] && v != son[u] && v != paiPath[u])
			Val[u].insert(1ll*w+dist2[v]);
	}
}

void remove(int u)
{
	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;

		if (ok[v] && v != paiPath[u] && Val[v].find(1ll*w+dist2[u]) != Val[v].end()) 
		{
			multiset<ll>::iterator it = Val[v].find(1ll*w+dist2[u]);
			Val[v].erase(it);
		}
	}
}

void dfs1(int u, int p, int dont)
{
	inPath[u] = false;
	remove(u);

	for (auto v: tree[u])
		if (v != p && v != dont)
			dfs1(v, u, dont);
}

void dfs2(int u, int p, int dont)
{
	ok[u] = true;
	add(u);

	for (auto v: tree[u])
		if (v != p && v != dont)
			dfs2(v, u, dont);
}

int main(void)
{
	scanf("%d %d %d %d", &n, &m, &s, &t);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	scanf("%d", &k);

	for (int i = 1; i <= k; i++)
	{
		int v;
		scanf("%d", &v);

		paiPath[v] = (i == 1 ? 0 : path.back());
		path.push_back(v);
	}

	for (int i = 1; i < k; i++)
		son[path[i-1]] = path[i];

	dijkstra();
	memset(mark, 0, sizeof mark);
	dijkstra2();

	for (int i = 1; i <= n; i++)
	{
		if (pai[i])
		{
			tree[i].push_back(pai[i]);
			tree[pai[i]].push_back(i);
		}
	}

	for (int i = 1; i <= n; i++)
		inPath[i] = true;

	for (int i = 0; i < path.size()-1; i++)
	{
		int u = path[i];

		dfs1(u, pai[u], path[i+1]);
		dfs2(u, pai[u], path[i+1]);

		ll ans = inf;
		for (int x = 1; x <= n; x++)
			if (ok[x] && Val[x].size() > 0)
				ans = min(ans, dist[x] + *(Val[x].begin()));

		if (ans == inf)
			printf("-1\n");
		else
			printf("%lld\n", ans);

	}
}
