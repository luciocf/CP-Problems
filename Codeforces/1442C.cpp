// Codeforces 1442C - Graph Transpositions
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;
const int mod = 998244353;
const int inf = 1e9+10;

int n;

int pot[maxn];

int dist[maxn][21];
bool mark[maxn][21];

pii dist_p[maxn][2];
bool mark_p[maxn][2];

vector<int> grafo[2][maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= 20; j++)
			dist[i][j] = inf;

	priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> fila;

	dist[1][0] = 0;
	fila.push({0, {1, 0}});

	while (!fila.empty())
	{
		int u = fila.top().ss.ff, k = fila.top().ss.ss; fila.pop();

		if (mark[u][k]) continue;
		mark[u][k] = 1;

		if (k < 20)
		{
			if (dist[u][k+1] > dist[u][k] + (1<<k))
			{
				dist[u][k+1] = dist[u][k] + (1<<k);
				fila.push({dist[u][k+1], {u, k+1}});
			}
		}

		for (auto v: grafo[k%2][u])
		{
			if (dist[v][k] > dist[u][k] + 1)
			{
				dist[v][k] = dist[u][k] + 1;
				fila.push({dist[v][k], {v, k}});
			}
		}
	}
}

void dijkstra_p(void)
{
	for (int i = 1; i <= n; i++)
		dist_p[i][0] = dist_p[i][1] = {inf, inf};

	priority_queue<pair<pii, pii>, vector<pair<pii, pii>>, greater<pair<pii, pii>>> fila;

	dist_p[1][0] = {0, 0};
	fila.push({dist_p[1][0], {1, 0}});

	while (!fila.empty())
	{
		pii D = fila.top().ff;
		int u = fila.top().ss.ff, q = fila.top().ss.ss; fila.pop();

		if (mark_p[u][q]) continue;
		mark_p[u][q] = 1;

		if (dist_p[u][q^1] > make_pair(dist_p[u][q].ff+1, dist_p[u][q].ss))
		{
			dist_p[u][q^1] = {dist_p[u][q].ff+1, dist_p[u][q].ss};
			fila.push({dist_p[u][q^1], {u, q^1}});
		}

		for (auto v: grafo[q][u])
		{
			if (dist_p[v][q] > make_pair(dist_p[u][q].ff, dist_p[u][q].ss+1))
			{
				dist_p[v][q] = make_pair(dist_p[u][q].ff, dist_p[u][q].ss+1);
				fila.push({dist_p[v][q], {v, q}});
			}
		}
	} 
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	pot[0] = 1;
	for (int i = 1; i < maxn; i++)
		pot[i] = (2ll*pot[i-1])%mod;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[0][u].push_back(v);
		grafo[1][v].push_back(u);
	}

	dijkstra();

	int ans = inf;

	for (int i = 0; i <= 20; i++)
		if (mark[n][i])
			ans = min(ans, dist[n][i]);

	if (ans != inf)
	{
		printf("%d\n", ans);
		return 0;
	}

	dijkstra_p();

	if (dist_p[n][0] < dist_p[n][1]) printf("%d\n", (pot[dist_p[n][0].ff] + dist_p[n][0].ss + mod - 1)%mod);
	else printf("%d\n", (pot[dist_p[n][1].ff] + dist_p[n][1].ss + mod - 1)%mod);
}
