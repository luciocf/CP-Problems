// BOI 2014 - Portals
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;
const int inf = 1e9+10;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int n, m, ox, oy, dx, dy;

int up[maxn][maxn], down[maxn][maxn];
int lft[maxn][maxn], rght[maxn][maxn];

int dist[maxn][maxn];
int dp[maxn][maxn];

bool mark[maxn][maxn];

char tab[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void init(void)
{
	for (int i = 0; i <= n+1; i++)
		for (int j = 0; j <= m+1; j++)
			if (tab[i][j] != '#')
				dp[i][j] = inf;
}

void bfs(void)
{
	for (int i = 0; i <= n+1; i++)
		for (int j = 0; j <= m+1; j++)
			dist[i][j] = inf;
 
	dist[ox][oy] = 0;
	priority_queue<piii, vector<piii>, greater<piii>> fila;
 
	fila.push({0, {ox, oy}});
 
	while (!fila.empty())
	{
		int x = fila.top().second.first, y = fila.top().second.second;
		fila.pop();
 
		if (mark[x][y]) continue;
 
		mark[x][y] = true;
 
		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];
			if (a < 0 || a > n+1 || b < 0 || b > m+1 || tab[a][b] == '#') continue;
 
			if (dist[x][y]+1 < dist[a][b])
			{
				dist[a][b] = dist[x][y]+1;
				fila.push({dist[a][b], {a, b}});
			}
		}

		int d = dp[x][y];
 
		int a = up[x][y]+1;

		if (dist[x][y]+d < dist[a][y])
		{
			dist[a][y] = dist[x][y]+d;
			fila.push({dist[a][y], {a, y}});
		}
 
		a = down[x][y]-1;

		if (dist[x][y]+d < dist[a][y])
		{
			dist[a][y] = dist[x][y]+d;
			fila.push({dist[a][y], {a, y}});
		}

		int b = lft[x][y]+1;
 
		if (dist[x][y]+d < dist[x][b])
		{
			dist[x][b] = dist[x][y]+d;
			fila.push({dist[x][b], {x, b}});
		}

		b = rght[x][y]-1;

		if (dist[x][y]+d < dist[x][b])
		{
			dist[x][b] = dist[x][y]+d;
			fila.push({dist[x][b], {x, b}});
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &tab[i][j]);

			if (tab[i][j] == 'S') ox = i, oy = j;
			if (tab[i][j] == 'C') dx = i, dy = j;
		}
	}

	for (int i = 0; i <= n; i++) tab[i][0] = tab[i][m+1] = '#';
	for (int j = 0; j <= m; j++) tab[0][j] = tab[n+1][j] = '#';

	for (int i = 0; i <= n+1; i++)
	{
		for (int j = 0; j <= m+1; j++)
		{
			if (tab[i][j] == '#') up[i][j] = i;
			else up[i][j] = up[i-1][j];
		}

		for (int j = 0; j <= m+1; j++)
		{
			if (tab[i][j] == '#') lft[i][j] = j;
			else lft[i][j] = lft[i][j-1];
		}
	}

	for (int i = n+1; i >= 0; i--)
	{
		for (int j = 0; j <= m+1; j++)
		{
			if (tab[i][j] == '#') down[i][j] = i;
			else down[i][j] = down[i+1][j];
 		}

 		for (int j = m+1; j >= 1; j--)
 		{
 			if (tab[i][j] == '#') rght[i][j] = j;
			else rght[i][j] = rght[i][j+1];
 		}
	}

	init();

	for (int i = 0; i <= n+1; i++)
	{
		for (int j = 0; j <= m+1; j++)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j-1]+1, i-up[i][j]});

		for (int j = m+1; j >= 1; j--)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j+1]+1, i-up[i][j]});
	}

	for (int i = n+1; i >= 1; i--)
	{
		for (int j = 0; j <= m+1; j++)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j-1]+1, down[i][j]-i});

		for (int j = m+1; j >= 1; j--)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j+1]+1, down[i][j]-i});
	}

	bfs();

	printf("%d\n", dist[dx][dy]);
}
