// USACO 2019/2020 - Greedy Pie Eaters
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 310;
const int maxm = 1e5+10;

int n, m;

int l[maxm], r[maxm], w[maxm];

int mx[maxn][maxn][maxn];
ll dp[maxn][maxn];

ll solve(int l, int r)
{
	if (l > r) return 0;
	if (dp[l][r] != -1) return dp[l][r];

	ll ans = 0;

	for (int i = l; i <= r; i++)
	{
		if (i < r) ans = max(ans, solve(l, i)+solve(i+1, r));

		ans = max(ans, solve(l, i-1)+solve(i+1, r)+1ll*mx[i][l][r]);
	}

	return dp[l][r] = ans;
}

int main(void)
{
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &w[i], &l[i], &r[i]);

		for (int j = l[i]; j <= r[i]; j++)
			mx[j][l[i]][r[i]] = max(mx[j][l[i]][r[i]], w[i]);
	}

	for (int i = 1; i <= n; i++)
	{
		for (int a = i; a >= 1; a--)
		{
			for (int b = i; b <= n; b++)
			{
				mx[i][a][b] = max(mx[i][a][b], mx[i][a][b-1]);
				mx[i][a][b] = max(mx[i][a][b], mx[i][a+1][b]);
			}
		}
	}

	memset(dp, -1, sizeof dp);

	printf("%lld\n", solve(1, n));
}
