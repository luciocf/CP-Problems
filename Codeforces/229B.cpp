// Codeforces 229B - Planets
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1100000000;

int n, m;

int dist[maxn];

bool mark[maxn];

unordered_map<int, int> on[maxn];

vector<pii> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii>> fila;
	
	int t = 0;
	while (on[1][t])
		t++;

	dist[1] = t;
	fila.push({t, 1});

	while (!fila.empty())
	{
		int u = fila.top().second, t = fila.top().first; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		int aux = t;
		while (on[u][aux])
			aux++;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist[v] > dist[u]+w+aux-t)
			{
				dist[v] = dist[u]+w+aux-t;
				fila.push({dist[v], v});
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	for (int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);

		for (int j = 1; j <= k; j++)
		{
			int t;
			scanf("%d", &t);

			on[i][t] = 1;
		}
	}

	dijkstra();

	if (dist[n] == inf) printf("-1\n");
	else printf("%d\n", dist[n]);
}
