// BOI 2019 - Nautilus
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;
const int maxm = 5e3+10;

bitset<maxn> bs[maxn], ant[maxn], mark[maxn];

char tab[maxn][maxn];
char s[maxm];

int main(void)
{
	int a, b, m;
	scanf("%d %d %d", &a, &b, &m);

	for (int i = 1; i <= a; i++)
	{
		for (int j = 1; j <= b; j++)
		{
			scanf(" %c", &tab[i][j]);

			if (tab[i][j] == '.')
			{
				mark[i][b-j+1] = 1;
				ant[i][b-j+1] = 1;
			}
		}
	}

	for (int i = 1; i <= m; i++)
		scanf(" %c", &s[i]);

	for (int p = 1; p <= m; p++)
	{
		for (int i = 1; i <= a; i++)
		{
			if (s[p] == 'N')
			{
				bs[i] = (ant[i+1] & mark[i]);
			}
			else if (s[p] == 'E')
			{
				bs[i] = ((ant[i] >> 1) & mark[i]);
			}
			else if (s[p] == 'S')
			{
				bs[i] = (ant[i-1] & mark[i]);
			}
			else if (s[p] == 'W')
			{
				bs[i] = ((ant[i] << 1) & mark[i]);
			}
			else
			{
				bs[i] = ((ant[i+1] | ant[i-1] | (ant[i] >> 1) | (ant[i] << 1)) & mark[i]);
			}
		}

		if (p != m)
			for (int i = 1; i <= a; i++)
				swap(bs[i], ant[i]);
	}

	int ans = 0;

	for (int i = 1; i <= a; i++)
		ans += bs[i].count();

	printf("%d\n", ans);
}
