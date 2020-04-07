// USACO 2016/2017 - Team Building
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;
const int mod = 1e9+9;

int n, m, k;
int a[maxn], b[maxn];

int dp[maxn][maxn][11];
int pref[maxn][maxn][11];

int main(void)
{
	freopen("team.in", "r", stdin); freopen("team.out", "w", stdout);

	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	sort(a+1, a+n+1); sort(b+1, b+m+1);

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			pref[i][j][0] = 1;

	for (int l = 1; l <= k; l++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (a[i] > b[j])
					dp[i][j][l] = pref[i-1][j-1][l-1];

				pref[i][j][l] = (pref[i][j-1][l] + dp[i][j][l])%mod;
			}
		}

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				pref[i][j][l] = (pref[i][j][l] + pref[i-1][j][l])%mod;
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans = (ans + dp[i][j][k])%mod;

	printf("%d\n", ans);
}
