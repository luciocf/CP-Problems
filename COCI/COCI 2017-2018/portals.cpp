// COCI 2017/2018 - Portals
// Lúcio Cardoso

// Same problem as Portals from BOI 2014
// Solution is explained here: https://github.com/boi-2014/tasks/blob/master/solutions/analysis/portals.tex

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 510;
const int inf = 1e9+10;
 
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
 
int n, m;
int ox, oy, dx, dy;
 
int direction[4][maxn][maxn];
 
int dist[maxn][maxn];
int dp[maxn][maxn];
 
bool mark[maxn][maxn];
 
char tab[maxn][maxn];
 
int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};
 
void calcDirection(void)
{
	for (int i = 0; i <= n+1; i++)
	{
		for (int j = 0; j <= m+1; j++)
		{
			if (tab[i][j] == '#')
				direction[0][i][j] = i;
			else
				direction[0][i][j] = direction[0][i-1][j];
		}
 
		for (int j = 0; j <= m+1; j++)
		{
			if (tab[i][j] == '#')
				direction[1][i][j] = j;
			else
				direction[1][i][j] = direction[1][i][j-1];
		}
	}
 
	for (int i = n+1; i >= 0; i--)
	{
		for (int j = 0; j <= m+1; j++)
		{
			if (tab[i][j] == '#')
				direction[2][i][j] = i;
			else
				direction[2][i][j] = direction[2][i+1][j];
 		}
 
 		for (int j = m+1; j >= 1; j--)
 		{
 			if (tab[i][j] == '#')
 				direction[3][i][j] = j;
			else
				direction[3][i][j] = direction[3][i][j+1];
 		}
	}
}
 
void solve(void)
{
	for (int i = 0; i <= n+1; i++)
	{
		for (int j = 0; j <= m+1; j++)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j-1]+1, i-direction[0][i][j]});
 
		for (int j = m+1; j >= 1; j--)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j+1]+1, i-direction[0][i][j]});
	}
 
	for (int i = n+1; i >= 1; i--)
	{
		for (int j = 0; j <= m+1; j++)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j-1]+1, direction[2][i][j]-i});
 
		for (int j = m+1; j >= 1; j--)
			if (tab[i][j] != '#')
				dp[i][j] = min({dp[i][j], dp[i][j+1]+1, direction[2][i][j]-i});
	}
}
 
void dijkstra(void)
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
 
		int delta = dp[x][y];
		int a = direction[0][x][y] + 1;
 
		if (dist[x][y]+delta < dist[a][y])
		{
			dist[a][y] = dist[x][y]+delta;
 
			fila.push({dist[a][y], {a, y}});
		}
 
		a = direction[2][x][y] - 1;
 
		if (dist[x][y]+delta < dist[a][y])
		{
			dist[a][y] = dist[x][y]+delta;
 
			fila.push({dist[a][y], {a, y}});
		}
 
		int b = direction[1][x][y] + 1;
 
		if (dist[x][y]+delta < dist[x][b])
		{
			dist[x][b] = dist[x][y]+delta;
 
			fila.push({dist[x][b], {x, b}});
		}
 
		b = direction[3][x][y] - 1;
 
		if (dist[x][y]+delta < dist[x][b])
		{
			dist[x][b] = dist[x][y]+delta;
 
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
 
			if (tab[i][j] == 'C') ox = i, oy = j;
 
			if (tab[i][j] == 'F') dx = i, dy = j;
		}
	}
 
	for (int i = 0; i <= n; i++)
		tab[i][0] = tab[i][m+1] = '#';
 
	for (int j = 0; j <= m; j++)
		tab[0][j] = tab[n+1][j] = '#';
 
	calcDirection();
 
	for (int i = 0; i <= n+1; i++)
		for (int j = 0; j <= m+1; j++)
			if (tab[i][j] != '#')
				dp[i][j] = inf;
 
	solve();
 
	dijkstra();
 
	if (dist[dx][dy] == inf)
		printf("nemoguce\n");
	else
		printf("%d\n", dist[dx][dy]);
}
