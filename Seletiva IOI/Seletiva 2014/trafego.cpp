// Seletiva IOI 2014 - Tráfego
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e4+5;
const int inf = 1e9+10;

int n, m;

int dist[maxn];

bool mark[maxn];

vector<pair<pii, pii>> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;

	dist[1] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> fila;
	fila.push({0, 1});

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first.first, w = pp.first.second;
			int g = pp.second.first, r = pp.second.second;

			int mod = (dist[u]+w)%(g+r);
			if (mod < g)
			{
				if (dist[v] > dist[u]+w)
				{
					dist[v] = dist[u]+w;
					fila.push({dist[v], v});
				}
			}
			else
			{
				if (dist[v] > dist[u]+w + (g+r-mod))
				{
					dist[v] = dist[u]+w + (g+r-mod);
					fila.push({dist[v], v});
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w, g, r;
		scanf("%d %d %d %d %d", &u, &v, &w, &g, &r);

		grafo[u].push_back({{v, w}, {g, r}});
	}

	dijkstra();

	if (dist[n] == inf) printf("-1\n");
	else printf("%d\n", dist[n]);
}
