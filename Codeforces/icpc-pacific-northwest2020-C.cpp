// ICPC Pacific Northwest 2020 Regional D1 - C - Coloring Contention
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int dist[maxn];

vector<int> grafo[maxn];

int bfs(int n)
{
	queue<int> fila;
	fila.push(1), dist[1] = 0;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[v] == -1)
			{
				dist[v] = dist[u]+1;
				fila.push(v);
			}
		}
	}

	return dist[n];
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

	printf("%d\n", bfs(n)-1);
}
