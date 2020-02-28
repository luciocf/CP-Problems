// COCI 2019/2020 - Zoo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+10;

int n, m;
char tab[maxn][maxn];

bool mark[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

int bfs(void)
{
	deque<pii> fila;

	fila.push_front({1, 1});
	mark[1][1] = 1;

	int ans = 1;
	char ant = tab[1][1];

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop_front();

		if (tab[x][y] != ant) ans++;
		ant = tab[x][y];

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > m || tab[a][b] == '*' || mark[a][b]) continue;

			if (tab[a][b] == tab[x][y]) fila.push_front({a, b});
			else fila.push_back({a, b});


			mark[a][b] = 1;
		}
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	printf("%d\n", bfs());
}
