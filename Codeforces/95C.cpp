// Codeforces 95C - Volleyball
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, int> pii;
 
const int maxn = 2e3+10;
const ll inf = 1e18+10;
 
int n, m;
 
int t[maxn], c[maxn];
 
ll dist[maxn][maxn];
 
bool mark[maxn];
 
vector<pii> grafo[maxn];
 
void dijkstra(int s)
{
	for (int i = 1; i <= n; i++)
		dist[s][i] = inf;
	dist[s][s] = 0;
 
	priority_queue<pii, vector<pii>, greater<pii>> fila;
	fila.push({0, s});
 
	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();
 
		if (mark[u]) continue;
		mark[u] = 1;
 
		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;
 
			if (dist[s][v] > dist[s][u]+1ll*w)
			{
				dist[s][v] = dist[s][u]+1ll*w;
				fila.push({dist[s][v], v});
			}
		}
	}
}
 
int main(void)
{
	int x, y;
	scanf("%d %d %d %d", &n, &m, &x, &y);
 
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
 
		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}
 
	for (int i = 1; i <= n; i++)
	{
		dijkstra(i);
		memset(mark, 0, sizeof mark);
	}
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &t[i], &c[i]);
		grafo[i].clear();
	}
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (j != i && dist[i][j] <= t[i])
				grafo[i].push_back({j, c[i]});
 
	dijkstra(x);
 
	if (dist[x][y] != inf) printf("%lld\n", dist[x][y]);
	else printf("-1\n");
}
