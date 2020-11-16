// Codeforces 715B - Complete The Graph
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e3+10;
const int maxm = 1e4+10;
const ll inf = 2e18+10;
const ll maxv = 1e18;

int n, m, L, s, t;

pair<pii, ll> edge[maxm];

ll dist[maxn];
pii pai[maxn];

ll ans[maxm];

bool mark[maxn], vis[maxm];

vector<pii> grafo[maxn];

void dijkstra(bool flag)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf, mark[i] = 0;

	dist[s] = 0;

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> fila;
	fila.push({0, s});

	while (!fila.empty())
	{
		int u = fila.top().ss;
		fila.pop();

		if (mark[u]) continue;

		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, e = pp.ss;
			ll w = ans[e];

			if (flag && w == 0) continue;

			if (w == 0) w = 1;

			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				pai[v] = {u, e};

				fila.push({dist[v], v});
			}
		}
	}
}

void dostuff(void)
{
	for (int i = 1; i <= m; i++)
		vis[i] = 0;

	int u = t;
	bool first = 1;

	while (u != s)
	{
		int e = pai[u].ss;
		vis[e] = 1;

		if (edge[e].ss == 0)
		{
			if (first) ans[e] = L - dist[t] + 1;
			else ans[e] = 1;

			first = 0;
		}

		u = pai[u].ff;
	}

	for (int i = 1; i <= m; i++)
		if (edge[i].ss == 0 && !vis[i])
			ans[i] = maxv;
}

int main(void)
{
	scanf("%d %d %d %d %d", &n, &m, &L, &s, &t);
	++s, ++t;

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		++u, ++v;

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});

		edge[i] = {{u, v}, w};
	}

	for (int i = 1; i <= m; i++)
		ans[i] = edge[i].ss;

	dijkstra(1);

	if (dist[t] < L)
	{
		printf("NO\n");
		return 0;
	}

	if (dist[t] == L)
	{
		printf("YES\n");

		for (int i = 1; i <= m; i++)
		{
			printf("%d %d ", edge[i].ff.ff-1, edge[i].ff.ss-1);

			if (edge[i].ss == 0) printf("%lld\n", maxv);
			else printf("%lld\n", ans[i]);
		}

		return 0;
	}

	dijkstra(0);

	if (dist[t] > L)
	{
		printf("NO\n");
		return 0;
	}

	if (dist[t] == L)
		dostuff();

	while (dist[t] < L)
	{
		dostuff();
		dijkstra(0);
	}

	printf("YES\n");
	for (int i = 1; i <= m; i++)
		printf("%d %d %lld\n", edge[i].ff.ff-1, edge[i].ff.ss-1, ans[i]);
}
