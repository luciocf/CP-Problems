// BOI 2017 - Cat in a tree
// Lúcio Cardoso

// Solution:

// 1. Root the tree arbitrarily. Suppose our current solution is a set S of nodes. Notice that
// it is always optimal to choose as next vertex in S the deepest node that doesn't 
// have distance <= D with any node in S.

// 2. Thus, with this greedy algorithm, we've reduced the problem to the following:

//	* Add a vertex U to a set of nodes S
//	* Query the closest node in S to a vertex U

// We can solve this reduced problem using centroid decomposition, by going upwards in the centroid tree.

// Complexity: O(n log n).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int n, D;

int order[maxn];

int sz[maxn], nivel[maxn];

int pai[maxn], dist[maxn][20];
int sub[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void dfsPre(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		dfsPre(v, u);
	}
}

void dfs(int u, int p)
{
	sz[u] = 1;
	for (auto v: grafo[u])
	{
		if (v == p || mark[v]) continue;

		dfs(v, u);
		sz[u] += sz[v];
	}
}

int centroid(int u, int p, int S)
{
	for (auto v: grafo[u])
		if (v != p && !mark[v] && sz[v] > S/2)
			return centroid(v, u, S);

	return u;
}

void upd(int u, int p, int x, int lvl)
{
	dist[u][lvl] = x;

	for (auto v: grafo[u])
		if (v != p && !mark[v])
			upd(v, u, x+1, lvl);
}

void decompose(int u, int p, int lvl)
{
	dfs(u, 0);

	int c = centroid(u, 0, sz[u]);

	mark[c] = true;
	pai[c] = p, nivel[c] = lvl;

	upd(c, 0, 0, lvl);

	for (auto v: grafo[c])
		if (!mark[v])
			decompose(v, c, lvl+1);
}

bool comp(int a, int b)
{
	return nivel[a] > nivel[b];
}

int main(void)
{
	scanf("%d %d", &n, &D);

	for (int i = 2; i <= n; i++)
	{
		int v;
		scanf("%d", &v);
		++v;

		grafo[i].push_back(v); grafo[v].push_back(i);
	}

	for (int i = 1; i <= n; i++)
	{
		order[i] = i;
		sub[i] = inf;
	}

	dfsPre(1, 0);
	sort(order+1, order+n+1, comp);

	decompose(1, 0, 0);

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		int u = order[i], v = u;
		int mn = inf;

		while (v)
		{
			mn = min(mn, dist[u][nivel[v]] + sub[v]);
			v = pai[v];
		}

		if (mn < D) continue;

		++ans, v = u;

		while (v)
		{
			sub[v] = min(sub[v], dist[u][nivel[v]]);
			v = pai[v];
		}
	}

	printf("%d\n", ans);
}

/*
	* bounds (maxn)
	* long long
	* all variables reset?
	* check if indexing is ok
	* off by one? (n-i+1) or (n-i)?
	* edge cases (n=0, n=1, n < 0, n=maxn)
*/
