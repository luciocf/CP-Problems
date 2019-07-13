// USACO Gold Dec 2011 - Grass Planting
// Lúcio Cardoso

// Solution:

// Use HLD with a BIT/Lazy Segment Tree

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int sz[maxn], nivel[maxn], pai[maxn];

int chain[maxn], head[maxn], pos[maxn], cc=1, pp;

int bit[maxn];

vector<int> grafo[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, pai[v] = u;
		dfs(v, u);

		sz[u] += sz[v];
	}
}

void hld(int u)
{
	if (!head[cc]) head[cc] = u;

	chain[u] = cc, pos[u] = ++pp;

	int maior = -1, ind = -1;
	for (auto v: grafo[u])
		if (v != pai[u] && sz[v] > maior)
			maior = sz[v], ind = v;

	if (ind != -1) hld(ind);

	for (auto v: grafo[u])
		if (v != pai[u] && v != ind)
			++cc, hld(v);
}

int lca(int u, int v)
{
	while (chain[u] != chain[v])
	{
		if (nivel[head[chain[u]]] > nivel[head[chain[v]]])
			u = pai[head[chain[u]]];
		else
			v = pai[head[chain[v]]];
	}

	return (nivel[u] > nivel[v] ? v : u);
}

void updPath(int u, int v)
{
	while (true)
	{
		if (chain[u] == chain[v])
		{
			upd(pos[v]+1, 1);
			upd(pos[u]+1, -1);
			return;
		}

		upd(pos[head[chain[u]]], 1);
		upd(pos[u]+1, -1);

		u = pai[head[chain[u]]];
	}
}

int queryPath(int u)
{
	return soma(pos[u]);
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);
	hld(1);


	for (int i = 1; i <= m; i++)
	{
		char op;
		int u, v;

		scanf(" %c %d %d", &op, &u, &v);

		if (op == 'P')
		{
			int l = lca(u, v);
			updPath(u, l); updPath(v, l);
		}
		else
		{
			if (pai[u] == v) printf("%d\n", queryPath(u));
			else printf("%d\n", queryPath(v));
		}
	}
}

/*
	* bounds (maxn)
	* long long
	* all variables reset?
	* check if indexing is ok
	* off by one? (n-i+1) or (n-i)?
	* edge cases (n=0, n=1, n < 0, n=maxn)
*/
