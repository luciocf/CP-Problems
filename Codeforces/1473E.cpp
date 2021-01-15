// Codeforces 1473E - Minimum Path
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

int n, m;

ll dist[maxn][2][2];
bool mark[maxn][2][2];

vector<pii> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		for (int a = 0; a < 2; a++)
			for (int b = 0; b < 2; b++)
				dist[i][a][b] = inf;

	priority_queue<pair<pii, pii>, vector<pair<pii, pii>>, greater<pair<pii, pii>>> fila;

	dist[1][0][0] = 0;
	fila.push({{0, 1}, {0, 0}});

	while (!fila.empty())
	{
		int u = fila.top().ff.ss, a = fila.top().ss.ff, b = fila.top().ss.ss; fila.pop();

		if (mark[u][a][b]) continue;
		mark[u][a][b] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, w = pp.ss;

			if (dist[v][a][b] > dist[u][a][b] + 1ll*w)
			{
				dist[v][a][b] = dist[u][a][b] + 1ll*w;
				fila.push({{dist[v][a][b], v}, {a, b}});
			}

			if (!a && dist[v][1][b] > dist[u][a][b] + 2ll*w)
			{
				dist[v][1][b] = dist[u][a][b] + 2ll*w;
				fila.push({{dist[v][1][b], v}, {1, b}});
			}

			if (!b && dist[v][a][1] > dist[u][a][b])
			{
				dist[v][a][1] = dist[u][a][b];
				fila.push({{dist[v][a][1], v}, {a, 1}});
			}

			if (!a && !b && dist[v][1][1] > dist[u][a][b] + 1ll*w)
			{
				dist[v][1][1] = dist[u][a][b] + 1ll*w;
				fila.push({{dist[v][1][1], v}, {1, 1}});
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

	dijkstra();

	for (int i = 2; i <= n; i++)
		printf("%lld ", dist[i][1][1]);
	printf("\n");
}
