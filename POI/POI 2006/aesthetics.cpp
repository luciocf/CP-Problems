// POI 2006 - Aesthetics
// Lúcio Cardoso

// Solution is similar to this one: https://github.com/stefdasca/CompetitiveProgramming/blob/master/POI/POI%2006-Aesthetics.cpp

#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

const int maxn = 2e3+1;
const int inf = 2e9+10;

int n, m;

int a[maxn];
int pref[maxn];

int last[maxn];

int dp[maxn][maxn];

int mn[2][maxn][maxn];

int line(int l, int r)
{
	return pref[r] - pref[l-1] + r - l;
}

int get(int l, int r)
{
	int ini = 1, fim = l-1, ans = l;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (line(l, r) >= line(mid, l-1)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pref[i] = pref[i-1] + a[i];
	}

	for (int i = 1; i <= n; i++)
		for (int j = i; j >= 1 && line(j, i) <= m; j--)
			last[i] = j;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mn[0][i][j] = mn[1][i][j] = dp[i][j] = inf;

	dp[1][1] = 0, mn[0][1][1] = -line(1, 1), mn[1][1][1] = line(1, 1);

	for (int r = 2; r <= n; r++)
	{
		for (int l = last[r]; l <= r; l++)
		{
			if (l == 1)
			{
				dp[l][r] = 0;
				mn[0][r][1] = -line(1, r), mn[1][r][1] = line(1, r);
				continue;
			}

			int ate = max(get(l, r), last[l-1]);

			if (ate < l) dp[l][r] = min(dp[l][r], line(l, r) + mn[0][l-1][ate]);

			if (last[l-1] <= ate-1)
				dp[l][r] = min(dp[l][r], mn[1][l-1][ate-1] - line(l, r));

			mn[0][r][l] = dp[l][r] - line(l, r);
			mn[1][r][l] = dp[l][r] + line(l, r);
		}

		for (int i = r-1; i >= 1; i--)
			mn[0][r][i] = min(mn[0][r][i], mn[0][r][i+1]);

		for (int i = last[r]+1; i <= r; i++)
			mn[1][r][i] = min(mn[1][r][i], mn[1][r][i-1]);
	}

	int ans = inf;

	for (int i = n; i >= 1 && line(i, n) <= m; i--)
		ans = min(ans, dp[i][n]);

	printf("%d\n", ans);
}
