// USACO 2014-2015 - Piggyback
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e4+10;
const long long inf = 2e18+10;

typedef long long ll;

int n, m;
int dist[3][maxn];

vector<int> grafo[maxn];

void bfs(int u, int q)
{
	queue<int> fila;

	fila.push(u), dist[q][u] = 0;

	while (!fila.empty())
	{
		int u = fila.front();
		fila.pop();

		for (auto v: grafo[u])
			if (dist[q][v] == -1)
				fila.push(v), dist[q][v] = dist[q][u]+1;
	}
}

int main(void)
{
	FILE *fin = fopen("piggyback.in", "r");
	FILE *fout = fopen("piggyback.out", "w");

	int b, e, p;
	fscanf(fin, "%d %d %d %d %d", &b, &e, &p, &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	memset(dist, -1, sizeof dist);

	bfs(1, 0); bfs(2, 1); bfs(n, 2);

	ll ans = inf;

	for (int i = 1; i <= n; i++)
		if (dist[0][i] != -1 && dist[1][i] != -1 && dist[2][i] != -1)
		ans = min(ans, 1ll*b*dist[0][i] + 1ll*e*dist[1][i] + 1ll*p*dist[2][i]);

	fprintf(fout, "%lld\n", ans);
}
