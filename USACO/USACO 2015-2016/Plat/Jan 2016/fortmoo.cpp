// USACO 2015/2016 - Fort Moo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;

int mn[maxn][maxn];

char tab[maxn][maxn];

int main(void)
{
	freopen("fortmoo.in", "r", stdin); freopen("fortmoo.out", "w", stdout);

	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	int ans = 0;

	memset(mn, -1, sizeof mn);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			bool mark = 0;

			for (int l = j; l >= 1; l--)
			{
				if (tab[i][l] == 'X') mark = 1;

				if (tab[i][j] == 'X' || tab[i][l] == 'X') mn[l][j] = -1;
				else if (mn[l][j] == -1 && !mark) mn[l][j] = i;

				if (!mark)
					ans = max(ans, (j-l+1)*(i-mn[l][j]+1));
			}
		}
	}

	printf("%d\n", ans);
}
