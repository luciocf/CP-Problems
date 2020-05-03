// DMOJ - DMOPC '19 Contest 5 P5 - Crazy Cyclic Coincidences
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

struct Edge
{
	int v, w, ind;
};

int path[maxn];

bool mark[maxn], mark_edge[maxn];

bool dp[2000010];

vector<int> ciclo;

vector<Edge> grafo[maxn];

void dfs(int u)
{
	mark[u] = 1;

	for (auto e: grafo[u])
	{
		int v = e.v, ind = e.ind;

		if (!mark[v])
		{
			mark_edge[ind] = 1;
			dfs(v);
		}
	}
}

void get_ciclo(int u, int p)
{
	mark[u] = 1;
	path[u] = p;

	for (auto e: grafo[u])
	{
		int v = e.v, w = e.w;

		if (!mark_edge[e.ind])
		{
			ciclo.push_back(w^path[v]^path[u]);
			continue;
		}

		if (!mark[v])
			get_ciclo(v, p^w);
	}
}

int main(void)
{
	int n, m, v;
	scanf("%d %d %d", &n, &m, &v);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w, i});
		grafo[v].push_back({u, w, i});
	}

	dfs(1);
	memset(mark, 0, sizeof mark);
	get_ciclo(1, 0);

	dp[0] = true;

	for (auto x: ciclo)
		if (!dp[x])
			for (int i = 2000000; i >= 1; i--)
				dp[i] |= dp[i^x];

	if (dp[v]) printf("yes\n");
	else printf("no\n");
}
