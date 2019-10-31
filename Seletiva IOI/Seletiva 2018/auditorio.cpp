// Seletiva IOI 2018 - Programa de Auditório
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 260;
const int maxs = 62510;

int a[maxn];
bool dp[maxn][maxs];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= n+1; i++)
		dp[i][0] = 1;

	for (int i = n; i >= 1; i--)
	{
		for (int j = maxs-1; j >= 1; j--)
		{
			if (j >= a[i]) dp[i][j] |= dp[i+1][j-a[i]];
			dp[i][j] |= dp[i+1][j];
		}
	}

	if (!dp[1][m])
	{
		printf("N\n");
		return 0;
	}

	printf("S\n");

	int at = 0, soma = 0;
	while (soma < m)
	{
		int last = -1;

		for (int i = at+1; i <= n; i++)
			if (soma+a[i] <= m && dp[i+1][m-soma-a[i]])
				last = i;

		at = last, soma += a[last];
		printf("%d ", last-1);
	}

	printf("\n");
}
