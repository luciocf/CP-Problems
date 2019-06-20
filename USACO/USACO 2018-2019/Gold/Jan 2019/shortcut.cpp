// USACO Gold Jan 2019 - Shortcut
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;
const int inf = 2e9+10;

typedef long long ll;
typedef pair<int, int> pii;

int c[maxn];

int dist[maxn];

int pai[maxn], sub[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

vector<int> tree[maxn];

void dijkstra(int n)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii> > fila;

	fila.push({0, 1}), dist[1] = 0;

	while (!fila.empty())
	{
		int u = fila.top().second;
		fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, d = pp.second;

			if (dist[v] > dist[u]+d)
			{
				dist[v] = dist[u]+d, pai[v] = u;
				fila.push({dist[v], v});
			}
			else if (dist[v] == dist[u]+d && u < pai[v])
			{
				dist[v] = dist[u]+d, pai[v] = u;
				fila.push({dist[v], v});
			}
		}
	}
}

void dfs(int u, int p)
{
	sub[u] = c[u];

	for (auto v: tree[u])
	{
		if (v == p) continue;

		dfs(v, u);

		sub[u] += sub[v];
	}
}

int main(void)
{
	FILE *fin = fopen("shortcut.in", "r");
	FILE *fout = fopen("shortcut.out", "w");

	int n, m, T;
	fscanf(fin, "%d %d %d", &n, &m, &T);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &c[i]);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		fscanf(fin, "%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	dijkstra(n);

	for (int i = 1; i <= n; i++)
	{
		int u = i, v = pai[i];

		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	dfs(1, 0);

	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, 1ll*sub[i]*(dist[i]-T));

	fprintf(fout, "%lld\n", ans);
}
