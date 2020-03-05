// Codeforces 1253F - Cheap Robot
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 3e5+10;
const ll inf = 1e18+10;

struct Edge
{
	int u, v;
	ll w;
} edge[maxn];

int n, m, k, q;

ll dist[maxn];

bool mark[maxn];

int pai[maxn], peso[maxn], nivel[maxn];
ll up[maxn];

vector<pii> grafo[maxn];

bool comp(Edge a, Edge b)
{
	return a.w < b.w;
}

void dijkstra(void)
{
	priority_queue<pii, vector<pii>, greater<pii>> fila;

	for (int i = 1; i <= n; i++)
	{
		dist[i] = inf;

		if (i <= k)
		{
			dist[i] = 0;
			fila.push({0ll, i});
		}
	}

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist[v] > dist[u]+1ll*w)
			{
				dist[v] = dist[u]+1ll*w;
				fila.push({dist[v], v});
			}
		}
	}
}

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return Find(pai[x]);
}

void Join(int x, int y, ll tt)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y], up[y] = tt;
}

int dfs(int u)
{
	if (pai[u] == u) return nivel[u] = 0;
	return nivel[u] = 1+dfs(pai[u]);
}

ll get(int u, int v)
{
	ll ans = 0;
	while (u != v)
	{
		if (nivel[u] > nivel[v]) ans = max(ans, up[u]), u = pai[u];
		else ans = max(ans, up[v]), v = pai[v];
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d %d", &n, &m, &k, &q);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});

		edge[i] = {u, v, w};
	}

	dijkstra();

	for (int i = 1; i <= m; i++)
		edge[i].w += 1ll*(dist[edge[i].u] + dist[edge[i].v]);

	sort(edge+1, edge+m+1, comp);

	init();
	for (int i = 1; i <= m; i++)
		Join(edge[i].u, edge[i].v, edge[i].w);

	for (int i = 1; i <= n; i++)
		dfs(i);

	while (q--)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		printf("%lld\n", get(a, b));
	}
}
