// JOI Final Round 2018 - Commuter Pass
// Lúcio Cardoso

// Solution is the same as in: https://codeforces.com/blog/entry/57637?#comment-413356

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

struct Edge
{
	int u, v, w;
} edge[maxn];

int n, m;
int S, T, U, V;

ll dist[4][maxn];
bool mark[maxn];

ll mn[maxn];

vector<int> dag[maxn], ord;
vector<pii> grafo[maxn];

void dijkstra(int q, int s)
{
	for (int i = 1; i <= n; i++)
	{
		dist[q][i] = inf;
		mark[i] = false;
	}

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	dist[q][s] = 0;
	fila.push({dist[q][s], s});

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();
		if (mark[u]) continue;

		mark[u] = true;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist[q][v] > dist[q][u] + 1ll*w)
			{
				dist[q][v] = dist[q][u] + 1ll*w;
				fila.push({dist[q][v], v});
			}
		}
	}
}

void dfs(int u)
{
	mark[u] = true;

	for (auto v: dag[u])
		if (!mark[v])
			dfs(v);

	ord.push_back(u);
}

ll get_mn(int a, int b)
{
	ll ans = inf;

	for (auto u: ord)
	{
		mn[u] = dist[b][u];

		for (auto v: dag[u])
			mn[u] = min(mn[u], mn[v]);

		ans = min(ans, dist[a][u] + mn[u]);
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d %d %d %d", &n, &m, &S, &T, &U, &V);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});

		edge[i] = {u, v, w};
	}

	dijkstra(0, S); dijkstra(1, T);
	dijkstra(2, U); dijkstra(3, V);

	for (int i = 1; i <= m; i++)
	{
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;

		if (dist[0][u] + 1LL*w + dist[1][v] == dist[0][T])
			dag[u].push_back(v);
		else if (dist[0][v] + 1LL*w + dist[1][u] == dist[0][T])
			dag[v].push_back(u);
	}

	memset(mark, 0, sizeof mark);

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);

	ll ans = min({dist[2][V], get_mn(2, 3), get_mn(3, 2)});

	printf("%lld\n", ans);
}
