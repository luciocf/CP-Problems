// USACO Gold Feb 2018 - Taming the Herd
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

int a[maxn];

int dp[maxn][maxn][maxn], minimo[maxn][maxn];

int main(void)
{
	freopen("taming.in", "r", stdin);
	freopen("taming.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn; j++)
			for (int l = 0; l < maxn; l++)
				dp[i][j][l] = minimo[i][j] = maxn;

	dp[1][1][1] = (a[1] != 0);
	minimo[1][1] = dp[1][1][1];

	for (int i = 2; i <= n; i++)
	{
		for (int k = 1; k <= i; k++)
		{
			for (int j = 1; j <= i; j++)
			{
				if (j != i)
					dp[i][k][j] = dp[i-1][k][j] + (a[i] != (i-j));
				else
					dp[i][k][j] = minimo[i-1][k-1] + (a[i] != 0);

				minimo[i][k] = min(minimo[i][k], dp[i][k][j]);
			}
		}
	}

	for (int i = 1; i <= n; i++)
		printf("%d\n", minimo[n][i]);
}
