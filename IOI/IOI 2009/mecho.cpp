// IOI 2009 - Mecho
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 810;

typedef pair<int, int> pii;

int n, s, ox, oy, dx, dy;
int dist[maxn][maxn];

char tab[maxn][maxn];

bool mark[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void bfs(void)
{
	queue<pii> fila;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (tab[i][j] == 'H')
				dist[i][j] = 0, fila.push({i, j});

	dist[dx][dy] = 1e9+10;

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop();

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];
			if (a < 1 || a > n || b < 1 || b > n || tab[a][b] == 'T' || tab[a][b] == 'D' || dist[a][b] != -1) continue;

			dist[a][b] = dist[x][y] + s;
			fila.push({a, b});
		}
	}
}

bool ok(int t)
{
	if (t*s >= dist[ox][oy]) return false;

	queue<pair<int, pii> > fila;

	memset(mark, 0, sizeof mark);

	mark[ox][oy] = 1;
	fila.push({t*s, {ox, oy}});

	while (!fila.empty())
	{
		int d = fila.front().first;
		int x = fila.front().second.first, y = fila.front().second.second;
		fila.pop();

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];
			if (a < 1 || a > n || b < 1 || b > n || tab[a][b] == 'T' || d+1 >= dist[a][b] || mark[a][b]) continue;

			if (tab[a][b] == 'D') return true;

			mark[a][b] = 1;
			fila.push({d+1, {a, b}});
		}
	}

	return false;
}

int busca(void)
{
	int ini = 0, fim = 640000*2, ans = -1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ini = mid+1, ans = mid;
		else fim = mid-1;
	}

	return ans;
}

int main(void)
{
	cin >> n >> s;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> tab[i][j];

			if (tab[i][j] == 'M') ox = i, oy = j;
			if (tab[i][j] == 'D') dx = i, dy = j;
		}
	}

	memset(dist, -1, sizeof dist);
	bfs();

	cout << busca() << "\n";
}
