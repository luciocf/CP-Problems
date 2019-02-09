// IOI 2013 - Dreaming
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;

typedef pair<int, int> pii;

int pai[MAXN], dist[MAXN], comp[MAXN], n, m, l, ind, maior;
bool mark[MAXN];
vector<pii> grafo[MAXN];

void DFS(int u, int p, int c)
{
	comp[c] = u, mark[u] = 1;

	for (auto v: grafo[u])
	{
		if (v.first == p) continue;

		DFS(v.first, u, c);
	}
}

void DFS2(int u, int p, int d)
{
	for (auto v: grafo[u]) 
	{
		if (v.first == p) continue;

		dist[v.first] = d+v.second;
		if (dist[v.first] > maior)
			maior = dist[v.first], ind = v.first;

		pai[v.first] = u;
		DFS2(v.first, u, dist[v.first]);
	}
}

int travelTime(int N, int M, int L, int A[], int B[], int T[])
{
	n = N, m = M, l = L;

	for (int i = 0; i < m; i++)
		grafo[A[i]].push_back({B[i], T[i]}), grafo[B[i]].push_back({A[i], T[i]});

	int c = -1;
	for (int i = 0; i < n; i++)
		if (!mark[i]) 
			DFS(i, -1, ++c);

	int maxdiam = 0, m1 = 0, m2 = 0, m3 = 0;
	for (int i = 0; i <= c; i++)
	{
		maior = 0, ind = comp[i];

		int u = comp[i];
		DFS2(u, -1, 0);

		u = ind;
		maior = 0, ind = comp[i];

		dist[u] = 0, pai[u] = -1;
		DFS2(u, -1, 0);

		maxdiam = max(maxdiam, maior);

		int v = ind, diam = maior, ans = maior;
		while (v != -1)
		{
			if (max(dist[v], diam-dist[v]) < ans)
				ans = max(dist[v], diam-dist[v]);
			v = pai[v];
		}

		if (ans >= m1) m3 = m2, m2 = m1, m1 = ans;
		else if (ans >= m2) m3 = m2, m2 = ans;
		else if (ans >= m3) m3 = ans;
	}

	if (c == 0) return maxdiam;
	else if (c == 1) return max(maxdiam, m1+m2+l);
	return max(maxdiam, max(m1+m2+l, m2+m3+2*l));
}
