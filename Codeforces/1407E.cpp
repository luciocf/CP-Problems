// Codeforces 1407E - Egor in the Republic of Dagestan
// Lúcio Cardoso

// Solution is the same as in: https://codeforces.com/blog/entry/82417?#comment-693262

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e5+10;
const int inf = 1e9+10;

int n, m;
int dist[maxn];

vector<pii> grafo[maxn];

int cor[maxn];
bool reach[maxn];

void bfs(void)
{
	queue<int> fila;
	fila.push(n), reach[n] = 1;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		map<pii, bool> mp;

		for (auto pp: grafo[u])
			mp[{pp.ff, pp.ss}] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, t = pp.ss;
			if (reach[v]) continue;

			if (cor[v] != -1 && cor[v] == t)
			{
				fila.push(v), reach[v] = 1, dist[v] = dist[u]+1;
				continue;
			}
			else if (cor[v] != -1) continue;

			if (mp[{v, 0}] && mp[{v, 1}])
			{
				fila.push(v), reach[v] = 1;
				dist[v] = dist[u]+1;
			}
			else if (!mp[{v, 0}]) cor[v] = 0;
			else cor[v] = 1;
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;

	for (int i = 1; i <= m; i++)
	{
		int u, v, t;
		cin >> u >> v >> t;

		grafo[v].push_back({u, t});
	}

	memset(cor, -1, sizeof cor);
	bfs();

	if (!reach[1]) printf("-1\n");
	else printf("%d\n", dist[1]);

	for (int i = 1; i <= n; i++)
	{
		if (cor[i] == -1) printf("0");
		else printf("%d", cor[i]);
	}

	printf("\n");
}
