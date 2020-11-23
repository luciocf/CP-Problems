// Codeforces 570E - Pig and Palindromes
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 505;
const int mod = 1e9+7;

int n, m;
char a[maxn][maxn];

int dp[2][maxn][maxn];

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &a[i][j]);

	if (a[1][1] != a[n][m])
	{
		printf("0\n");
		return 0;
	}

	for (int tot = n+m-2; tot >= 0; tot--)
	{
		for (int h1 = 0; h1 <= min(tot, n-1); h1++)
		{
			for (int h2 = 0; h2 <= min(tot, n-1); h2++)
			{
				int q = tot%2;

				int x1 = 1+h1, y1 = 1+tot-h1;
				int x2 = n-h2, y2 = m-(tot-h2);

				if (x1 == x2 && y1 == y2) dp[q][h1][h2] = 1;
				else if ((x1 == x2-1 && y1 == y2) || (x1 == x2 && y1 == y2-1)) dp[q][h1][h2] = 1;
				else if ((x1 == n && y1 == m) || (x2 == 1 && y2 == 1)) dp[q][h1][h2] = 0;
				else
				{
					int ans = 0;

					if (x1 < n && x2 > 1 && a[x1+1][y1] == a[x2-1][y2]) ans = (ans + dp[q^1][h1+1][h2+1])%mod;
					if (x1 < n && y2 > 1 && a[x1+1][y1] == a[x2][y2-1]) ans = (ans + dp[q^1][h1+1][h2])%mod;
					if (y1 < m && x2 > 1 && a[x1][y1+1] == a[x2-1][y2]) ans = (ans + dp[q^1][h1][h2+1])%mod;
					if (y1 < m && y2 > 1 && a[x1][y1+1] == a[x2][y2-1]) ans = (ans + dp[q^1][h1][h2])%mod;

					dp[q][h1][h2] = ans;
				}
			}
		}
	}

	printf("%d\n", dp[0][0][0]);
}
