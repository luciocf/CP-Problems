// Codeforces 1416D - Graph and Queries
// Lúcio Cardoso

/* Solution:

After reading all queries, add every edge that wasn't removed in a DSU. After that, process the removed
edges in reverse order and add them in the same DSU. For each edge in the DSU tree, store the time it was
removed in the queries.

After building the DSU tree, store the entire subtree of a node (this takes O(n log n) memory) and sort it decreasingly
by value p.

To answer a query in a vertex v and time t, find its last reachable ancestor u (i.e the last one such that every edge
in the path v -> u has time > t); this can be done by simply going up in the tree, since its depth is O(log n). Then, all that's
left to find is the largest element in the subtree of u that can reach u in time t. To do this, just keep a pointer for the subtree
of every node, and increase the pointer of u while the value in sub[u][ptr[u]] is 0 or while sub[u][ptr[u]] can't reach u.

NOTE: Don't use path compression, since we need the DSU tree.

Complexity: O(n log n)

*/

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e5+10;

struct DSU
{
	int pai[maxn], peso[maxn], tempo[maxn];

	int ptr[maxn];
	vector<int> sub[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return Find(pai[x]);
	}

	void Join(int x, int y, int tt)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
		tempo[y] = tt;
	}

	int get(int u, int tt)
	{
		while (pai[u] != u && tempo[u] > tt) u = pai[u];
		return u;
	}
} dsu;

int a[maxn];

pii edge[maxn];
bool mark_edge[maxn];

pii query[maxn];

int main(void)
{
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d %d", &edge[i].ff, &edge[i].ss);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d", &query[i].ff, &query[i].ss);

		if (query[i].ff == 2) mark_edge[query[i].ss] = 1;
	}

	dsu.init(n);
	for (int i = 1; i <= m; i++)
		if (!mark_edge[i])
			dsu.Join(edge[i].ff, edge[i].ss, q+1);

	for (int i = q; i >= 1; i--)
	{
		if (query[i].ff == 2)
		{
			int e = query[i].ss;

			dsu.Join(edge[e].ff, edge[e].ss, i);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		int u = i;

		while (true)
		{
			dsu.sub[u].push_back(i);

			if (dsu.pai[u] == u) break;

			u = dsu.pai[u];
		}
	}

	for (int i = 1; i <= n; i++)
		sort(dsu.sub[i].begin(), dsu.sub[i].end(), [&] (int x, int y) {return a[x] > a[y];});

	for (int i = 1; i <= q; i++)
	{
		if (query[i].ff == 2) continue;

		int u = dsu.get(query[i].ss, i);

		while (dsu.ptr[u] < dsu.sub[u].size() && (a[dsu.sub[u][dsu.ptr[u]]] == -1 || dsu.get(dsu.sub[u][dsu.ptr[u]], i) != u))
			dsu.ptr[u]++;

		if (dsu.ptr[u] == dsu.sub[u].size()) printf("0\n");
		else
		{
			printf("%d\n", a[dsu.sub[u][dsu.ptr[u]]]);

			a[dsu.sub[u][dsu.ptr[u]++]] = -1;
		}
	}
}
