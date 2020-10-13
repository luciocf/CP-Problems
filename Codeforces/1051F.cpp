// Codeforces 1051F - The Shortest Statement
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

int n, m;

ll dist[43][maxn];
bool mark[maxn];

int back[43], aux;

vector<pii> grafo[maxn], tree[maxn];

struct BinaryLifting
{
	int nivel[maxn];
	ll D[maxn];
	int tab[maxn][20];

	void dfs(int u, int p)
	{
		for (auto pp: tree[u])
		{
			int v = pp.ff, w = pp.ss;
			if (v == p) continue;

			tab[v][0] = u, nivel[v] = nivel[u] + 1, D[v] = D[u] + 1ll*w;
			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int j = 1; j <= 19; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int lca(int u, int v)
	{
		if (nivel[u] < nivel[v]) swap(u, v);

		for (int i = 19; i >= 0; i--)
			if (nivel[u]-(1<<i) >= nivel[v])
				u = tab[u][i];

		if (u == v) return u;

		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
				u = tab[u][i], v = tab[v][i];

		return tab[u][0];
	}

	ll dist(int u, int v)
	{
		return D[u] + D[v] - 2ll*D[lca(u, v)]; 
	}
} LCA;

void dfs(int u, int p)
{
	mark[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;

		if (mark[v])
		{
			if (v != p) back[++aux] = u;
			continue;
		}

		tree[u].push_back({v, w});
		tree[v].push_back({u, w});

		dfs(v, u);
	}
}

void dijkstra(int k)
{
	for (int i = 1; i <= n; i++)
		dist[k][i] = inf, mark[i] = 0;

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> fila;

	dist[k][back[k]] = 0;
	fila.push({0ll, back[k]});

	while (!fila.empty())
	{
		int u = fila.top().ss; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, w = pp.ss;

			if (dist[k][v] > dist[k][u] + 1ll*w)
			{
				dist[k][v] = dist[k][u] + 1ll*w;
				fila.push({dist[k][v], v});
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

	dfs(1, 0);
	LCA.dfs(1, 0); LCA.build();

	for (int i = 1; i <= aux; i++)
		dijkstra(i);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		ll ans = LCA.dist(u, v);

		for (int i = 1; i <= aux; i++)
			ans = min(ans, LCA.dist(u, back[i]) + dist[i][v]);

		printf("%lld\n", ans);
	}
}
