// USACO Gold Dec 2018 - Fine Dining
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10;
const int inf = 1e9+10;

typedef pair<int, int> pii;

int n, k;
int a[maxn];

int dist1[maxn], dist2[maxn];

bool mark[maxn];

bool haybale[maxn];

vector<pii> grafo[maxn];

void dijkstra1(void)
{
	for (int i = 1; i < n; i++)
		dist1[i] = inf;

	dist1[n] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> fila;
	fila.push({0, n});

	while (!fila.empty())
	{
		int u = fila.top().second;
		fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, d = pp.second;

			if (dist1[v] > dist1[u]+d)
			{
				dist1[v] = dist1[u]+d;
				fila.push({dist1[v], v});
			}
		}
	}
}

void dijkstra2(void)
{	
	memset(mark, 0, sizeof mark);

	for (int i = 1; i <= n; i++)
		dist2[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	for (int i = 1; i <= n; i++)
	{
		if (haybale[i])
		{
			dist2[i] = dist1[i]-a[i];
			fila.push({dist2[i], i});
		}
	}

	while (!fila.empty())
	{
		int u = fila.top().second;
		fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, d = pp.second;

			if (dist2[v] > dist2[u]+d)
			{
				dist2[v] = dist2[u]+d;
				fila.push({dist2[v], v});
			}
		}
	}
}

int main(void)
{
	FILE *fin = fopen("dining.in", "r");
	FILE *fout = fopen("dining.out", "w");

	int m;
	fscanf(fin, "%d %d %d", &n, &m, &k);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		fscanf(fin, "%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	for (int i = 1; i <= k; i++)
	{
		int u;

		fscanf(fin, "%d", &u);
		fscanf(fin, "%d", &a[u]);
		
		haybale[u] = 1;
	}

	dijkstra1(); dijkstra2();

	for (int i = 1; i < n; i++)
	{
		if (dist2[i] <= dist1[i])
			fprintf(fout, "1\n");
		else
			fprintf(fout, "0\n");
	}
}
