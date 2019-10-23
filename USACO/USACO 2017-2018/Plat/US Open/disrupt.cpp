// USACO 2017/2018 - Disruption
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e4+10;

int n;
int in[maxn], en[maxn], tt;

int ans[maxn];

int cost[maxn];

pii edge[maxn];

set<pii> st[maxn];

vector<pii> grafo[maxn];
vector<int> sai[maxn];

void dfs(int u, int p)
{
	in[u] = ++tt;

	for (auto v: grafo[u])
		if (v.first != p)
			dfs(v.first, u);

	en[u] = tt;
}

void merge(int u, int v)
{
	if (st[u].size() > st[v].size())
	{
		for (auto pp: st[v])
			st[u].insert(pp);
	}
	else
	{
		for (auto pp: st[u])
			st[v].insert(pp);

		swap(st[u], st[v]);
	}

	st[v].clear();
}

void solve(int u, int p, int e)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first;
		if (v == p) continue;

		solve(v, u, pp.second);

		merge(u, v);
	}

	for (auto i: sai[u])
	{
		int a = edge[i].first, b = edge[i].second;

		if (a == u) swap(a, b);

		if (in[a] >= in[u] && en[a] <= en[u])
		{
			if (st[u].find({cost[i], i}) != st[u].end())
				st[u].erase({cost[i], i});
		}
		else
			st[u].insert({cost[i], i});
	}

	for (auto it = st[u].begin(); it != st[u].end();)
	{
		int i = (*it).second;

		int a = edge[i].first, b = edge[i].second;

		if (in[a] >= in[u] && en[a] <= en[u] && in[b] >= in[u] && en[b] <= en[u])
			it = st[u].erase(it);
		else break;
	}

	if (st[u].size()) ans[e] = (*st[u].begin()).first;
	else ans[e] = -1;
}

int main(void)
{
	freopen("disrupt.in", "r", stdin);
	freopen("disrupt.out", "w", stdout);

	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});
	}

	dfs(1, 0);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		edge[i] = {u, v};
		cost[i] = w;

		sai[u].push_back(i); sai[v].push_back(i);
	}

	solve(1, 0, 0);

	for (int i = 1; i < n; i++)
		printf("%d\n", ans[i]);
}
