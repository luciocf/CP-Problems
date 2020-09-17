// POI 2008 - Bike Paths
// Lúcio Cardoso

/* Solution:

Finds SCCs and get the resulting compressed DAG. Now process vertices in reverse topological order.
The answer for vertex u (from the DAG, not original graph), is equal to sz[u] + sum (ans[v]), where sz[u]
is the amount of vertices from the original graph in the SCC u and v is a direct neighbour from u.

The final answer for a vertex u is ans[scc[u]]-1. This algorithm doesn't overcount anything because
there is only one path between two vertices in different SCCs.

Complexity: O(n+m)
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10;

int in[maxn], tt, low[maxn];
int comp[maxn], cc;

int sz[maxn], ans[maxn];
bool mark[maxn];
vector<int> ord;

map<int, int> mp[maxn];

vector<int> grafo[maxn], dag[maxn];

stack<int> stk;

void dfs(int u)
{
	in[u] = low[u] = ++tt;
	stk.push(u);

	for (auto v: grafo[u])
	{
		if (in[v])
		{
			low[u] = min(low[u], in[v]);
			continue;
		}

		dfs(v);

		low[u] = min(low[u], low[v]);
	}

	if (in[u] != low[u]) return;

	++cc;

	while (true)
	{
		int x = stk.top(); stk.pop();

		comp[x] = cc, in[x] = maxn;
		++sz[cc];

		if (x == u) return;
	}
}

void topo(int u)
{
	mark[u] = 1;

	for (auto v: dag[u])
		if (!mark[v])
			topo(v);

	ord.push_back(u);
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
	}

	for (int i = 1; i <= n; i++)
		if (!in[i])
			dfs(i);

	for (int u = 1; u <= n; u++)
		for (auto v: grafo[u])
			if (comp[u] != comp[v] && mp[comp[u]].find(comp[v]) == mp[comp[u]].end())
				dag[comp[u]].push_back(comp[v]), mp[comp[u]][comp[v]] = 1;

	for (int i = 1; i <= cc; i++)
		if (!mark[i])
			topo(i);

	for (auto u: ord)
	{
		ans[u] = sz[u];

		for (auto v: dag[u])
			ans[u] += ans[v];
	}

	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[comp[i]]-1);
}
