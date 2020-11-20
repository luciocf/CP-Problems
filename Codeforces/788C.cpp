// Codeforces 788C - The Great Mixing
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int a[maxn];

int dist[2010];
bool mark[2010];

vector<int> grafo[2010];

void bfs(int n)
{
	queue<int> fila;

	for (int i = 1; i <= n; i++)
	{
		dist[a[i]+1000] = 1;
		fila.push(a[i]+1000);
	}

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
}

int main(void)
{	
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i]);

		a[i] -= n;

		if (mark[a[i]+n]) continue;
		mark[a[i]+n] = 1;

		for (int v = -1000; v <= 1000; v++)
			if (v+a[i] >= -1000 && v+a[i] <= 1000)
				grafo[v+1000].push_back(v+a[i]+1000);
	}

	memset(dist, -1, sizeof dist);

	bfs(m);

	printf("%d\n", dist[1000]);
}
