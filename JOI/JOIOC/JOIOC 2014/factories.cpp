// JOI Open Contest 2014 - Factories
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "factories.h"

#define ff first
#define ss second

using namespace std;

const int maxn = 5e5+10;
const long long inf = 1e18+10;

typedef pair<int, int> pii;
typedef long long ll;

int n;
int sz[maxn], pai[maxn], nivel[maxn];

ll dist[maxn][19], child[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

int dfs(int u, int p)
{
	sz[u] = 1;
	for (auto v: grafo[u])
		if (v.first != p && !mark[v.first])
			sz[u] += dfs(v.first, u);

	return sz[u];
}

int centroid(int S, int u, int p)
{
	for (auto v: grafo[u])
		if (v.first != p && !mark[v.first] && sz[v.first] > S/2)
			return centroid(S, v.first, u);

	return u;
}

void upd(int u, int p, int lvl, ll d)
{	
	dist[u][lvl] = d;

	for (auto v: grafo[u])
		if (v.first != p && !mark[v.first])
			upd(v.first, u, lvl, d+(ll)v.second);
}

void decompose(int u, int p, int lvl)
{
	dfs(u, -1);

	int c = centroid(sz[u], u, -1);
	mark[c] = 1, nivel[c] = lvl;

	upd(c, -1, lvl, 0LL);

	pai[c] = p;

	for (auto v: grafo[c])
		if (!mark[v.first])
			decompose(v.first, c, lvl+1);
}

void Init(int N, int A[], int B[], int D[])
{
	n = N;

	for (int i = 0; i < n-1; i++)
	{
		grafo[A[i]].push_back({B[i], D[i]});
		grafo[B[i]].push_back({A[i], D[i]});
	}

	for (int i = 0; i < n; i++)
		child[i] = inf;

	decompose(0, -1, 0);
}

long long Query(int S, int X[], int T, int Y[])
{
	int s = S, t = T;

	for (int i = 0; i < t; i++)
	{
		int v = Y[i];
		
		while (v != -1)
		{
			child[v] = min(child[v], dist[Y[i]][nivel[v]]);

			v = pai[v];
		}
	}

	ll ans = inf;

	for (int i = 0; i < s; i++)
	{
		int v = X[i];

		while (v != -1)
		{
			ans = min(ans, dist[X[i]][nivel[v]]+child[v]);

			v = pai[v];
		}
	}

	for (int i = 0; i < t; i++)
	{
		int v = Y[i];
		
		while (v != -1)
		{
			child[v] = inf;

			v = pai[v];
		}
	}

	return ans;
}
