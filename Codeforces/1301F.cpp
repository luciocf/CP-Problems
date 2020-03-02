// Codeforces 1301F - Super Jaber
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+10;

int n, m, k;

int cor[maxn][maxn];

int dist[41][maxn][maxn];
int dist_aux[maxn][maxn];

bool mark[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

vector<pii> vert[41];

void bfs(int c)
{
	memset(mark, 0, sizeof mark);
	deque<pii> fila;

	fila.push_front({0, c});
	mark[0][c] = 1;

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop_front();

		if (x == 0)
		{
			for (auto pp: vert[y])
			{
				int a = pp.first, b = pp.second;
				if (mark[a][b]) continue;

				dist[c][a][b] = dist[c][x][y]+1, mark[a][b] = 1;
				fila.push_back({a, b});
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				int a = x+linha[i], b = y+coluna[i];
				if (a < 1 || a > n || b < 1 || b > m || mark[a][b]) continue;

				dist[c][a][b] = dist[c][x][y]+1, mark[a][b] = 1;
				fila.push_back({a, b});
			}

			if (!mark[0][cor[x][y]])
			{
				dist[c][0][cor[x][y]] = dist[c][x][y], mark[0][cor[x][y]] = 1;
				fila.push_front({0, cor[x][y]});
			}
		}
	}
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &cor[i][j]);

			vert[cor[i][j]].push_back({i, j});
		}
	}

	for (int i = 1; i <= k; i++)
		bfs(i);

	int q;
	scanf("%d", &q);

	memset(mark, 0, sizeof mark);

	while (q--)
	{
		int ox, oy, dx, dy;
		scanf("%d %d %d %d", &ox, &oy, &dx, &dy);

		int ans = abs(dx-ox) + abs(dy-oy);

		for (int i = -k; i <= k; i++)
		{
			for (int j = -(k-abs(i)); abs(j)+abs(i) <= k; j++)
			{
				int a = ox+i, b = oy+j;
				if (a < 1 || a > n || b < 1 || b > m) continue;

				ans = min(ans, abs(i) + abs(j) + dist[cor[a][b]][dx][dy]);

				mark[a][b] = dist_aux[a][b] = 0;
			}
		}

		printf("%d\n", ans);
	}
}
