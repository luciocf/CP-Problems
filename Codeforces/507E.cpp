// Codeforces 507E - Breaking Good
// Lúcio Cardoso

// Solution: 

// As can be seen in the editorial, the problem becomes finding the shortest path that minimizes
// the amount of broken edges. To find that, we can use Dijkstra's algorithm, using the amount of broken edges
// as a tiebreaker.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1e9+10;

struct Edge
{
	int u, v, w;
} edge[maxn];

int n, m;

int d1[maxn], d2[maxn];
pii pai[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

map<pii, int> mark_edge;

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		d1[i] = d2[i] = inf;

	priority_queue<pair<pii, int>, vector<pair<pii, int>>, greater<pair<pii, int>>> fila;

	d1[1] = d2[1] = 0;
	fila.push({{d1[1], d2[1]}, 1});

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (d1[v] > d1[u]+1 || (d1[v] == d1[u]+1 && d2[v] > d2[u] + (w == 0)))
			{
				d1[v] = d1[u]+1, d2[v] = d2[u] + (w == 0);
				fila.push({{d1[v], d2[v]}, v});

				pai[v] = {u, w};
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	int C = 0;

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});

		edge[i] = {u, v, w};

		if (w == 1) C++;
	}

	dijkstra();

	printf("%d\n", 2*d2[n] + C - d1[n]);

	int v = n;
	while (v != 1)
	{
		int p = pai[v].ff, w = pai[v].ss;

		if (w == 0) printf("%d %d 1\n", v, p);
		else mark_edge[{v, p}] = mark_edge[{p, v}] = 1;

		v = p;
	}

	for (int i = 1; i <= m; i++)
		if (edge[i].w == 1 && !mark_edge[{edge[i].u, edge[i].v}])
			printf("%d %d 0\n", edge[i].u, edge[i].v);
}
