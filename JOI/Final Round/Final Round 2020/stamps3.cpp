// JOI Final Round 2020 - Collecting Stamps 3
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 210;
const ll inf = 1e18;
 
int n, L;
int x[maxn], t[maxn];
 
ll dp[maxn][maxn][maxn][2];
 
int main(void)
{
	scanf("%d %d", &n, &L);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i]);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &t[i]);
 
	for (int l = 0; l <= n; l++)
		for (int r = 0; r <= n; r++)
			for (int k = 0; k <= n; k++)
				dp[l][r][k][0] = dp[l][r][k][1] = inf;
 
	dp[0][0][0][0] = dp[0][0][0][1] = 0;
 
	x[n+1] = L;
 
	for (int l = 0; l <= n; l++)
	{
		for (int r = 0; r+l <= n; r++)
		{
			for (int k = 0; k <= n; k++)
			{
				ll ans = inf;
 
				if (l == 0 && r == 0 && k == 0) ans = 0;
 
				int pos_l = n-l+1;
 
				if (l > 0)
				{
					ll c1 = dp[l-1][r][k][0] + 1ll*x[pos_l+1] - 1ll*x[pos_l];
					ll c2 = dp[l-1][r][k][1] + 1ll*L-1ll*x[pos_l] + 1ll*x[r];
 
					ans = min(ans, c1);
					ans = min(ans, c2);
 
					if (k > 0)
					{
						c1 -= dp[l-1][r][k][0]; c1 += dp[l-1][r][k-1][0];
						c2 -= dp[l-1][r][k][1]; c2 += dp[l-1][r][k-1][1];
 
						if (c1 <= 1ll*t[pos_l]) ans = min(ans, c1);
						if (c2 <= 1ll*t[pos_l]) ans = min(ans, c2);
					}
				}
 
				dp[l][r][k][0] = ans;
 
				ans = inf;
 
				if (l == 0 && r == 0 && k == 0) ans = 0;
 
				if (r > 0)
				{
					ll c1 = dp[l][r-1][k][1] + 1ll*x[r] - 1ll*x[r-1];
					ll c2 = dp[l][r-1][k][0] + 1ll*L-1ll*x[pos_l] + 1ll*x[r];
 
					ans = min(ans, c1);
					ans = min(ans, c2);
 
					if (k > 0)
					{
						c1 -= dp[l][r-1][k][1]; c1 += dp[l][r-1][k-1][1];
						c2 -= dp[l][r-1][k][0]; c2 += dp[l][r-1][k-1][0];
 
						if (c1 <= 1ll*t[r]) ans = min(ans, c1);
						if (c2 <= 1ll*t[r]) ans = min(ans, c2);
					}
				}
 
				dp[l][r][k][1] = ans;
			}
		}
	}
 
	int ans = 0;
 
	for (int l = 0; l <= n; l++)
		for (int r = 0; r+l <= n; r++)
			for (int k = 0; k <= n; k++)
				if (dp[l][r][k][0] != inf || dp[l][r][k][1] != inf)
					ans = max(ans, k);
 
	printf("%d\n", ans);
}
