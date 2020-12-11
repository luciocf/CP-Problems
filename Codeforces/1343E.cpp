// Codeforces 1343E - Weights Distributing
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

int dist[3][maxn];

ll p[maxn];

vector<int> grafo[maxn];

void bfs(int s, int q)
{
	queue<int> fila;

	dist[q][s] = 0;
	fila.push(s);

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[q][v] == -1)
			{
				dist[q][v] = dist[q][u] + 1;
				fila.push(v);
			}
		}
	}
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n, m, a, b, c;
		scanf("%d %d %d %d %d", &n, &m, &a, &b, &c);

		for (int i = 1; i <= n; i++)
		{
			grafo[i].clear();
			dist[0][i] = dist[1][i] = dist[2][i] = -1;
		}

		for (int i = 1; i <= m; i++)
			scanf("%lld", &p[i]);

		sort(p+1, p+m+1);

		for (int i = 1; i <= m; i++)
			p[i] += p[i-1];

		for (int i = 1; i <= m; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}

		bfs(a, 0); bfs(b, 1); bfs(c, 2);

		ll ans = inf;

		for (int i = 1; i <= n; i++)
		{
			int da = dist[0][i], db = dist[1][i], dc = dist[2][i];

			if (da + db + dc <= m)
				ans = min(ans, p[da+db]-p[db] + 2ll*p[db] + p[da+db+dc]-p[da+db]);
		}

		printf("%lld\n", ans);
	}
}
