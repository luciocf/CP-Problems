// Codeforces 543B - Destroying Roads
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;

int dist[maxn][maxn];

vector<int> grafo[maxn];

void bfs(int s)
{
	queue<int> fila;
	fila.push(s);

	dist[s][s] = 0;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[s][v] == -1)
			{
				dist[s][v] = dist[s][u]+1;
				fila.push(v);
			}
		}
	}
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	memset(dist, -1, sizeof dist);
	for (int i = 1; i <= n; i++)
		bfs(i);

	int s1, t1, l1, s2, t2, l2;
	scanf("%d %d %d %d %d %d", &s1, &t1, &l1, &s2, &t2, &l2);

	int ans = -1;

	if (dist[s1][t1] <= l1 && dist[s2][t2] <= l2)
		ans = m-dist[s1][t1]-dist[s2][t2];

	for (int u = 1; u <= n; u++)
	{
		for (int v = 1; v <= n; v++)
		{
			int D1 = min(dist[s1][u]+dist[v][t1], dist[s1][v]+dist[u][t1]);
			int D2 = min(dist[s2][u]+dist[v][t2], dist[s2][v]+dist[u][t2]);

			if (D1 + dist[u][v] > l1 || D2 + dist[u][v] > l2) continue;

			ans = max(ans, m - D1 - D2 - dist[u][v]);
		}
	}

	printf("%d\n", ans);
}
