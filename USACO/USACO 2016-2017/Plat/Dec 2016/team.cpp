// USACO 2016/2017 - Team Building
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;
const int mod = 1e9+9;

int n, m, k;
int a[maxn], b[maxn];

int dp[maxn][maxn][12], pref[maxn][maxn][12]; 

int main(void)
{
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);

	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	sort(a+1, a+n+1); sort(b+1, b+m+1);
		
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			pref[i][j][0] = 1;

	for (int t = 1; t <= k; t++)
	{
		for (int l = 1; l <= n; l++)
		{
			for (int r = 1; r <= m; r++)
			{
				if (a[l] > b[r])
					dp[l][r][t] = pref[l-1][r-1][t-1];

				pref[l][r][t] = (dp[l][r][t] + pref[l][r-1][t])%mod;
			}

			for (int r = 1; r <= m; r++)
				pref[l][r][t] = (pref[l][r][t]+pref[l-1][r][t])%mod;
		}
	}

	int ans = 0;

	for (int l = 1; l <= n; l++)
		for (int r = 1; r <= m; r++)
			ans = (ans+dp[l][r][k])%mod;

	printf("%d\n", ans);
}
