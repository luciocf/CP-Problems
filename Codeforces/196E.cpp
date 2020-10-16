// Codeforces 196E - Opening Portals
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

int n, m, k;

ll dist[maxn];
int source[maxn];
bool mark[maxn];

int lista[maxn];

vector<pii> grafo[maxn];

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
	}
} dsu;

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	for (int i = 1; i <= k; i++)
	{
		dist[lista[i]] = 0, source[lista[i]] = lista[i];
		fila.push({0, lista[i]});
	}

	while (!fila.empty())
	{
		int u = fila.top().ss; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, w = pp.ss;

			if (dist[v] > dist[u] + 1ll*w)
			{
				dist[v] = dist[u] + 1ll*w;
				source[v] = source[u];

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

	scanf("%d", &k);

	bool tem_1 = 0;

	for (int i = 1; i <= k; i++)
	{
		scanf("%d", &lista[i]);

		if (lista[i] == 1) tem_1 = 1;
	}

	dijkstra();

	vector<pair<ll, pii>> edges;

	for (int u = 1; u <= n; u++)
	{
		for (auto pp: grafo[u])
		{
			int v = pp.ff, w = pp.ss;

			if (source[u] != source[v])
				edges.push_back({1ll*w + dist[u] + dist[v], {source[u], source[v]}});
		}
	}

	sort(edges.begin(), edges.end());

	dsu.init(n);
	ll ans = 0;

	for (auto e: edges)
	{
		int u = e.ss.ff, v = e.ss.ss;

		if (dsu.Find(u) != dsu.Find(v))
		{
			dsu.Join(u, v);
			ans += e.ff;
		}
	}

	printf("%lld\n", ans + (!tem_1 ? dist[1] : 0));
}
