// IZhO 2018 - Evacuation Plan
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n;

int pai[maxn], peso[maxn], edge[maxn], tt;
int nivel[maxn];

bool city[maxn], mark[maxn];

pii dist[maxn];

vector<pii> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = {inf, i};

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	for (int i = 1; i <= n; i++)
	{
		if (city[i])
		{
			fila.push({0, i});
			dist[i] = {0, i};
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

			if (dist[v].first > dist[u].first+w)
			{
				dist[v].first = dist[u].first+w;
				fila.push(dist[v]);
			}
		}
	}
}

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1, edge[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y], edge[y] = tt;
}

int dfs(int u)
{
	mark[u] = 1;

	if (u == Find(u)) return 0;

	if (mark[pai[u]]) return (nivel[u] = nivel[pai[u]]+1);

	return (nivel[u] = dfs(pai[u])+1);
}

int get(int u, int v)
{
	int ans = 1;

	while (u != v)
	{
		if (nivel[u] > nivel[v]) ans = max(ans, edge[u]), u = pai[u];
		else ans = max(ans, edge[v]), v = pai[v];
	}

	return ans;
}

bool comp(pii a, pii b) {return a.first > b.first;}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	int k;
	scanf("%d", &k);

	for (int i = 1; i <= k; i++)
	{
		int u;
		scanf("%d", &u);

		city[u] = 1;
	}

	dijkstra();

	sort(dist+1, dist+n+1, comp);

	memset(mark, 0, sizeof mark);

	init();

	for (int i = 1; i <= n; i++)
	{
		int u = dist[i].second;

		++tt;

		for (auto pp: grafo[u])
		{
			int v = pp.first;

			if (mark[v])
				Join(u, v);
		}

		mark[u] = 1;
	}

	memset(mark, 0, sizeof mark);

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		printf("%d\n", dist[get(u, v)].first);
	}
}
