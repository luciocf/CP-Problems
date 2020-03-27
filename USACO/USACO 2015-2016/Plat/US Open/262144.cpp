// USACO 2015/2016 - 262144
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

int a[maxn];

int dp[maxn][80];

int main(void)
{
	freopen("262144.in", "r", stdin); freopen("262144.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j < 80; j++)
		{
			if (j == a[i]) dp[i][a[i]] = i+1;
			else if (dp[i][j-1]) dp[i][j] = dp[dp[i][j-1]][j-1];
		}
	}

	int ans = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < 80; j++)
			if (dp[i][j])
				ans = max(ans, j);

	printf("%d\n", ans);
}
