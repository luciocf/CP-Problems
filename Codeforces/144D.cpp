// Codeforces 144D - Missile Silos
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

int dist[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

void dijkstra(int s)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;
	dist[s] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> fila;
	fila.push({0, s});

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist[v] > dist[u]+w)
			{
				dist[v] = dist[u]+w;
				fila.push({dist[v], v});
			}
		}
	}
}

int main(void)
{
	int s;
	scanf("%d %d %d", &n, &m, &s);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});

		edge[i] = {u, v, w};
	}

	dijkstra(s);

	int l;
	scanf("%d", &l);

	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		Edge e = edge[i];

		if (dist[e.u] < l && dist[e.v] < l && dist[e.u]+dist[e.v]+e.w == 2*l)
		{
			ans++;
			continue;
		}

		if (dist[e.u] < l && l-dist[e.u] < e.w && dist[e.v] + e.w - (l-dist[e.u]) > l) ans++;
		if (dist[e.v] < l && l-dist[e.v] < e.w && dist[e.u] + e.w - (l-dist[e.v]) > l) ans++;
	}

	for (int i = 1; i <= n; i++)
		if (dist[i] == l)
			ans++;

	printf("%d\n", ans);
}
