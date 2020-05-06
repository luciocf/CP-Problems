// DMOJ - UTS Open '15 #5 - Distribution Channel (Hard)
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1e9+10;

struct Edge
{
	int u, v, w;
} edge[maxn];

int n, m;
int cost_mst, ans;

int pai[maxn], peso[maxn];

int in[maxn], en[maxn], tt;

set<pii> st[maxn];

vector<pii> grafo[maxn];
vector<int> sai[maxn];

bool comp(Edge a, Edge b) {return a.w < b.w;}

void init(void)
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

void dfs(int u, int p)
{
	in[u] = ++tt;

	for (auto e: grafo[u])
		if (e.first != p)
			dfs(e.first, u);

	en[u] = tt;
}

bool inside(int v, int u)
{
	return (in[v] >= in[u] && en[v] <= en[u]);
}

void merge(int u, int v)
{
	if (st[v].size() <= st[u].size())
	{
		for (auto it: st[v])
			st[u].insert(it);
	}
	else
	{
		for (auto it: st[u])
			st[v].insert(it);

		swap(st[u], st[v]);
	}

	st[v].clear();
}

void solve(int u, int p, int edge_p)
{
	for (auto e: grafo[u])
	{
		int v = e.first;
		if (v == p) continue;

		solve(v, u, e.second);

		merge(u, v);
	}

	for (auto e: sai[u])
	{
		int v = (edge[e].u == u ? edge[e].v : edge[e].u);

		if (inside(v, u))
		{
			if (st[u].find({edge[e].w, e}) != st[u].end())
				st[u].erase({edge[e].w, e});
		}
		else
			st[u].insert({edge[e].w, e});
	}

	if (!p) return;

	for (auto it = st[u].upper_bound({edge_p, inf}); it != st[u].end(); )
	{
		int a = edge[it->second].u, b = edge[it->second].v;

		if ((inside(a, u) && inside(b, u)))
			it = st[u].erase(it);
		else
		{
			ans = min(ans, cost_mst - edge_p + it->first);
			return;
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);

	sort(edge+1, edge+m+1, comp);

	init();

	for (int i = 1; i <= m; i++)
	{
		if (Find(edge[i].u) != Find(edge[i].v))
		{
			Join(edge[i].u, edge[i].v);

			grafo[edge[i].u].push_back({edge[i].v, edge[i].w});
			grafo[edge[i].v].push_back({edge[i].u, edge[i].w});

			cost_mst += edge[i].w;
		}
		else
		{
			sai[edge[i].u].push_back(i);
			sai[edge[i].v].push_back(i);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (Find(i) != Find(1))
		{
			printf("-1\n");
			return 0;
		}
	}

	ans = inf;
	dfs(1, 0); solve(1, 0, 0);

	if (ans == inf) printf("-1\n");
	else printf("%d\n", ans);
}
