// Seletiva IOI 2017 - Caminhos
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 2e5+10;
const ll inf = 1e14+10;

int n, m;

int edge[maxn], peso[maxn];
ll dist[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

void bfs(void)
{
	queue<int> fila;

	for (int i = 1; i <= n; i++)
		edge[i] = maxn;

	fila.push(1), mark[1] = 1, edge[1] = 0;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto pp: grafo[u])
		{
			int v = pp.first;
			if (!mark[v])
			{
				edge[v] = edge[u]+1, mark[v] = 1;
				fila.push(v);
			}
		}
	}
}

void dijkstra(ll K)
{
	for (int i = 1; i <= n; i++)
		dist[i] = 1e18+10, peso[i] = maxn;

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	fila.push({0ll, 1}), dist[1] = 0ll, peso[1] = 0;

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first;
			ll d = pp.second;

			if (dist[v] > dist[u]+d+K || (dist[v] == dist[u]+d+K && peso[v] > peso[u]+1))
			{
				dist[v] = dist[u]+d+K;
				peso[v] = peso[u]+1;
				fila.push({dist[v], v});
			}
		}
	}
}

bool ok(ll K)
{
	memset(mark, 0, sizeof mark);

	dijkstra(K);

	for (int i = 1; i <= n; i++)
		if (peso[i] != edge[i])
			return 0;

	return 1;
}

ll busca(void)
{
	ll ini = 0ll, fim = inf, ans = -1ll;

	while (ini <= fim)
	{
		ll mid = (ini+fim)/2ll;

		if (ok(mid)) ans = mid, fim = mid-1ll;
		else ini = mid+1ll;
	}

	return ans;
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

	bfs();

	printf("%lld\n", busca());
}
