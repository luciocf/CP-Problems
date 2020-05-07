// Codeforces 545E - Paths and Trees
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 3e5+10;
const ll inf = 1e18+10;

struct Edge
{
	int v, w, ind;
};

int n, m, s;
ll soma;

ll dist[maxn];
bool mark[maxn];

int w_pai[maxn];
int edge_pai[maxn];

vector<Edge> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;
	dist[s] = 0, w_pai[s] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> fila;
	fila.push({0, s});

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto e: grafo[u])
		{
			int v = e.v, w = e.w, ind = e.ind;

			if ((dist[v] > dist[u]+1ll*w) || (dist[v] == dist[u]+1ll*w && w < w_pai[v]))
			{
				soma -= 1ll*w_pai[v];

				dist[v] = dist[u]+1ll*w, w_pai[v] = w, edge_pai[v] = ind;

				soma += 1ll*w_pai[v];

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

		grafo[u].push_back({v, w, i});
		grafo[v].push_back({u, w, i});
	}

	scanf("%d", &s);

	dijkstra();

	printf("%lld\n", soma);
	for (int i = 1; i <= n; i++)
		if (i != s)
			printf("%d ", edge_pai[i]);
	printf("\n");
}
