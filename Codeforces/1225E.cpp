// Codeforces 1225E - Rock is Push
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;
const int mod = 1e9+7;

int n, m;
char tab[maxn][maxn];

int tot[2][maxn][maxn];

int soma_down[maxn][maxn], soma_right[maxn][maxn];

int dp[2][maxn][maxn];

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	for (int i = n; i >= 1; i--)
	{
		for (int j = m; j >= 1; j--)
		{
			tot[0][i][j] = tot[0][i][j+1] + (tab[i][j] == 'R');

			tot[1][i][j] = tot[1][i+1][j] + (tab[i][j] == 'R');
		}
	}

	for (int i = n; i >= 1; i--)
	{
		for (int j = m; j >= 1; j--)
		{
			if (i == n && j == m)
			{
				dp[0][i][j] = dp[1][i][j] = (tab[i][j] == 'R' ? 0 : 1);

				soma_down[i][j] = (soma_down[i][j+1] + dp[1][i][j])%mod;
				soma_right[i][j] = (soma_right[i+1][j] + dp[0][i][j])%mod;

				continue;
			}

			dp[0][i][j] = (soma_down[i][j+1] - soma_down[i][m - tot[0][i][j+1] + 1] + mod)%mod;
			dp[1][i][j] = (soma_right[i+1][j] - soma_right[n - tot[1][i+1][j] + 1][j] + mod)%mod;

			soma_down[i][j] = (soma_down[i][j+1] + dp[1][i][j])%mod;
			soma_right[i][j] = (soma_right[i+1][j] + dp[0][i][j])%mod;
		}
	}

	if (n == 1 && m == 1)
	{
		printf("%d\n", (tab[1][1] == 'R' ? 0 : 1));
		return 0;
	}

	printf("%d\n", (dp[0][1][1] + dp[1][1][1])%mod);
}
