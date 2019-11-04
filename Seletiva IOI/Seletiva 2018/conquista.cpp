// Seletiva IOI 2018 - Conquista
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;
const int inf = 1e9+10;

int n, m;
int a[maxn][maxn];
int dp[2][maxn][maxn];

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= m; i++)
	{
		dp[0][1][i] = dp[0][1][i-1]+a[1][i];
		dp[1][1][i] = -inf;
	}

	for (int i = 2; i <= n; i++)
	{
		dp[0][i][0] = -inf;

		for (int j = 1; j <= m; j++)
			dp[0][i][j] = a[i][j] + max({dp[0][i][j-1], dp[0][i-1][j], dp[1][i-1][j]});

		dp[1][i][m+1] = -inf;

		for (int j = m; j >= 1; j--)
			dp[1][i][j] = a[i][j] + max({dp[1][i][j+1], dp[0][i-1][j], dp[1][i-1][j]});
	}

	printf("%d\n", max(dp[0][n][m], dp[1][n][m]));
}
