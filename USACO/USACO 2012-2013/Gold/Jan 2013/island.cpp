// USACO 2012/2013 - Island Travels
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 16;
const int maxm = 55;
const int inf = 1e9+10;

int n, m, C;

char tab[maxm][maxm];

int comp[maxm][maxm];
bool mark[maxm][maxm];

int aux[maxn][maxm][maxm], dist[maxn][maxn];

int dp[1<<maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

int dfs(int x, int y, int cc)
{
	comp[x][y] = cc;

	for (int i = 0; i < 4; i++)
	{
		int a = x+linha[i], b = y+coluna[i];
		if (a < 1 || a > n || b < 1 || b > m || comp[a][b] || tab[a][b] != 'X') continue;

		dfs(a, b, cc);
	}
}

void bfs(int cc)
{
	memset(mark, 0, sizeof mark);

	deque<pii> fila;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (comp[i][j] == cc)
				fila.push_front({i, j}), mark[i][j] = 1;

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop_front();

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > m || tab[a][b] == '.' || mark[a][b]) continue;

			mark[a][b] = 1;

			if (tab[a][b] == 'S')
			{
				aux[cc][a][b] = aux[cc][x][y]+1;
				fila.push_back({a, b});
			}
			else
			{
				aux[cc][a][b] = aux[cc][x][y];
				fila.push_front({a, b});
			}
		}
	}
}

int solve(int mask, int u)
{
	if (mask == (1<<C)-1) return 0;
	if (dp[mask][u] != -1) return dp[mask][u];

	int ans = inf;

	for (int v = 0; v < C; v++)
		if (!(mask&(1<<v)))
			ans = min(ans, dist[u+1][v+1] + solve(mask^(1<<v), v));

	return dp[mask][u] = ans;
}

int main(void)
{
	freopen("island.in", "r", stdin); freopen("island.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (tab[i][j] == 'X' && !comp[i][j])
				dfs(i, j, ++C);

	for (int i = 1; i <= C; i++)
		bfs(i);

	for (int i = 1; i <= C; i++)
		for (int j = i+1; j <= C; j++)
			dist[i][j] = dist[j][i] = inf;

	for (int c = 1; c <= C; c++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (tab[i][j] == 'X')
					dist[c][comp[i][j]] = min(dist[c][comp[i][j]], aux[c][i][j]);

	memset(dp, -1, sizeof dp);

	int ans = inf;
	for (int i = 0; i < C; i++)
		ans = min(ans, solve(1<<i, i));

	printf("%d\n", ans);
}
