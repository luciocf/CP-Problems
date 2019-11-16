// Seletiva IOI 2015 - Caminho
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 310;

int n;
int tab[maxn][maxn];

int dist[maxn][maxn];

bool mark[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void bfs(int k)
{
	queue<pii> fila;

	fila.push({1, 1}), mark[1][1] = 1, dist[1][1] = 0;

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop();

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > n || tab[a][b] > k || mark[a][b]) continue;

			fila.push({a, b});
			mark[a][b] = 1, dist[a][b] = dist[x][y]+1;
		}
	}
}

bool ok(int k)
{
	if (tab[1][1] > k) return 0;

	memset(mark, 0, sizeof mark); memset(dist, 0, sizeof dist);

	bfs(k);

	return mark[n][n];
}

int busca(void)
{
	int ini = 1, fim = 1e9+10, ans = 1e9+10;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &tab[i][j]);

	int k = busca();

	memset(mark, 0, sizeof mark); memset(dist, 0, sizeof dist);

	bfs(k);

	printf("%d %d\n", k, dist[n][n]+1);
}
