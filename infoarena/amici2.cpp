// infoarena - Amici2
// Lúcio Cardoso

// Solution:

// 1. Notice the answer to the problem is equal to log(diameter_of_graph).

// 2. Run a BFS from node 1 and find the largest depth. Notice the diameter
// will be at most twice that depth. Hence, to solve the problem, we can print the log of that
// largest depth, since our answer will be off by at most 1.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e4+10;

int dist[maxn];

vector<int> grafo[maxn];

int bfs(void)
{
	memset(dist, -1, sizeof dist);
	queue<int> fila;

	int ans = 0;

	dist[1] = 0, fila.push(1);

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[v] == -1)
			{
				dist[v] = dist[u]+1;
				fila.push(v);

				ans = max(ans, dist[v]);
			}
		}
	}

	return ans;
}

int main(void)
{
	freopen("amici2.in", "r", stdin);
	freopen("amici2.out", "w", stdout);

	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);

		for (int i = 1; i <= n; i++)
			grafo[i].clear();

		for (int i = 1; i <= m; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}

		int D = bfs(), ans = 0;

		while (D > 1)
		{
			ans++;
			D /= 2;
		}

		printf("%d\n", ans+1);
	}
}
