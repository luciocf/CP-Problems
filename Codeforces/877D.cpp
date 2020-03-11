// Codeforces 877D - Olya and Energy Drinks
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+10;

int n, m, k;
int ox, oy, dx, dy;

int L[maxn][maxn], R[maxn][maxn];
int U[maxn][maxn], D[maxn][maxn];

int dist[maxn][maxn];

char tab[maxn][maxn];

set<int> linha[maxn], coluna[maxn];

void bfs(void)
{
	queue<pii> fila;
	fila.push({ox, oy});

	linha[ox].erase(oy); coluna[oy].erase(ox);

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop();

		auto it = linha[x].upper_bound(y);
		for (; it != linha[x].end() && *it <= R[x][y] && *it-y <= k; )
		{
			fila.push({x, *it});
			dist[x][*it] = dist[x][y]+1;

			coluna[*it].erase(x);
			it = linha[x].erase(it);
		}

		it = linha[x].lower_bound(max(y-k, L[x][y]));
		for (; it != linha[x].end() && *it < y; )
		{
			fila.push({x, *it});
			dist[x][*it] = dist[x][y]+1;

			coluna[*it].erase(x);
			it = linha[x].erase(it);
		}

		it = coluna[y].upper_bound(x);
		for (; it != coluna[y].end() && *it <= D[x][y] && *it-x <= k; )
		{
			fila.push({*it, y});
			dist[*it][y] = dist[x][y]+1;

			linha[*it].erase(y);
			it = coluna[y].erase(it);
		}

		it = coluna[y].lower_bound(max(x-k, U[x][y]));
		for (; it != coluna[y].end() && *it < x; )
		{
			fila.push({*it, y});
			dist[*it][y] = dist[x][y]+1;

			linha[*it].erase(y);
			it = coluna[y].erase(it);
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
			scanf(" %c", &tab[i][j]);

			if (tab[i][j] == '.')
			{
				linha[i].insert(j);
				coluna[j].insert(i);
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (tab[i][1] != '#') L[i][1] = 1;

		for (int j = 2; j <= m; j++)
		{
			if (tab[i][j] == '#') continue;

			if (tab[i][j-1] == '#') L[i][j] = j;
			else L[i][j] = L[i][j-1];
		}

		if (tab[i][m] != '#') R[i][m] = m;

		for (int j = m-1; j >= 1; j--)
		{
			if (tab[i][j] == '#') continue;

			if (tab[i][j+1] == '#') R[i][j] = j;
			else R[i][j] = R[i][j+1];
		}
	}

	for (int j = 1; j <= m; j++)
	{
		if (tab[1][j] != '#') U[1][j] = 1;

		for (int i = 2; i <= n; i++)
		{
			if (tab[i][j] == '#') continue;

			if (tab[i-1][j] == '#') U[i][j] = i;
			else U[i][j] = U[i-1][j];
		}

		if (tab[n][j] != '#') D[n][j] = n;

		for (int i = n-1; i >= 1; i--)
		{
			if (tab[i][j] == '#') continue;

			if (tab[i+1][j] == '#') D[i][j] = i;
			else D[i][j] = D[i+1][j];
		}
	}

	scanf("%d %d %d %d", &ox, &oy, &dx, &dy);

	bfs();

	if (linha[dx].find(dy) == linha[dx].end())
		printf("%d\n", dist[dx][dy]);
	else
		printf("-1\n");
}
