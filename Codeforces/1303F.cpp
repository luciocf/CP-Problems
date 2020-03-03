// Codeforces 1303F - Number of Components
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 310;
const int maxq = 2e6+10;

struct Query
{
	int x, y, c;
} query[maxq];

int n, m;

int pai[maxn*maxn], peso[maxn*maxn];

int cor[maxn][maxn];

int ans[maxq];

int primeiro[maxn][maxn];

bool mark[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

int pos(int i, int j)
{
	return (i-1)*m + j;
}

void init(void)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			pai[pos(i, j)] = pos(i, j), peso[pos(i, j)] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

int main(void)
{
	scanf("%d %d", &n, &m);

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
		scanf("%d %d %d", &query[i].x, &query[i].y, &query[i].c);

	for (int i = 1; i <= q; i++)
	{
		init();
		memset(mark, 0, sizeof mark);

		int j;
		int diff = 0;
		for (j = i; j <= q && query[j].c == query[i].c; j++)
		{
			mark[query[j].x][query[j].y] = 1;

			if (primeiro[query[j].x][query[j].y] < i)
				primeiro[query[j].x][query[j].y] = j, ++diff;
		}
		j--;

		int cc = n*m-diff;

		for (int a = 1; a <= n; a++)
		{
			for (int b = 1; b <= m; b++)
			{
				if (mark[a][b]) continue;

				for (int t = 0; t < 4; t++)
				{
					int c = a+linha[t], d = b+coluna[t];

					if (c < 1 || c > n || d < 1 || d > m || mark[c][d]) continue;

					if (cor[a][b] == cor[c][d] && Find(pos(a, b)) != Find(pos(c, d)))
						Join(pos(a, b), pos(c, d)), cc--;
				}
			}
		}

		ans[j] += cc;
		for (int l = j; l > i; l--)
		{
			int a = query[l].x, b = query[l].y;

			if (primeiro[a][b] == l)
			{
				mark[a][b] = 0, cc++;

				for (int t = 0; t < 4; t++)
				{
					int c = a+linha[t], d = b+coluna[t];

					if (c < 1 || c > n || d < 1 || d > m || mark[c][d]) continue;

					if (cor[a][b] == cor[c][d] && Find(pos(a, b)) != Find(pos(c, d)))
						Join(pos(a, b), pos(c, d)), cc--;
				}
			}

			ans[l-1] += cc;
		}

		init();

		cc = 1;
		ans[i] += cc;
		mark[query[i].x][query[i].y] = 1, cor[query[i].x][query[i].y] = query[i].c;

		for (int l = i+1; l <= j; l++)
		{
			int a = query[l].x, b = query[l].y;

			if (primeiro[a][b] == l)
			{
				mark[a][b] = 1, cor[a][b] = query[i].c, cc++;

				for (int t = 0; t < 4; t++)
				{
					int c = a+linha[t], d = b+coluna[t];

					if (c < 1 || c > n || d < 1 || d > m || !mark[c][d]) continue;

					if (Find(pos(a, b)) != Find(pos(c, d)))
						Join(pos(a, b), pos(c, d)), cc--;
				}
			}

			ans[l] += cc;
		}

		i = j;
	}

	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
