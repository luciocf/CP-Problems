// USACO 2017-2018 - Subsequence Reversal
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int a[maxn];

int dp[maxn][maxn][maxn][maxn];

int solve(int l, int r, int al, int ar)
{
	if (l > r) return 0;
	if (dp[l][r][al][ar] != -1) return dp[l][r][al][ar];

	int ans = 0;

	ans = max(ans, solve(l+1, r, al, ar));
	ans = max(ans, solve(l, r-1, al, ar));

	if (a[l] >= al && a[l] <= ar)
	{	
		ans = max(ans, 1+solve(l+1, r, a[l], ar));
		ans = max(ans, 1+solve(l+1, r-1, al, a[l]));

		if (a[r] >= al && a[r] <= ar && a[l] >= a[r] && l != r)
			ans = max(ans, 2+solve(l+1, r-1, a[r], a[l]));
	}

	if (a[r] >= al && a[r] <= ar)
	{
		ans = max(ans, 1+solve(l, r-1, al, a[r]));
		ans = max(ans, 1+solve(l+1, r-1, a[r], ar));
	}
	
	return dp[l][r][al][ar] = ans;
}

int main(void)
{
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int ans = 1;

	memset(dp, -1, sizeof dp);

	printf("%d\n", solve(1, n, 0, 51));
}
