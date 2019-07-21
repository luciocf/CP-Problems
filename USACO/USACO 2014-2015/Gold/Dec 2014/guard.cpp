// USACO Gold Dec 2014 - Guard
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 21;
const int inf = 1e9+10;

int n;
int h[maxn], w[maxn], s[maxn];

int dp[1<<maxn];

int solve(int mask)
{
	if (!mask) return inf;
	if (dp[mask] != -1) return dp[mask];

	int ans = -inf;
	long long soma = 0ll;

	for (int i = 0; i < n; i++)
		if (mask&(1<<i))
			soma += 1ll*w[i];

	for (int i = 0; i < n; i++)
	{
		if (!(mask&(1<<i))) continue;

		int r = soma-w[i];

		if (s[i] >= r)
			ans = max(ans, min(s[i]-r, solve(mask^(1<<i))));
	}

	return dp[mask] = ans;
}

int main(void)
{
	freopen("guard.in", "r", stdin);
	freopen("guard.out", "w", stdout);

	int H;
	scanf("%d %d", &n, &H);

	for (int i = 0; i < n; i++)
		scanf("%d %d %d", &h[i], &w[i], &s[i]);

	memset(dp, -1, sizeof dp);

	int ans = -inf;

	for (int mask = 0; mask < (1<<n); mask++)
	{
		solve(mask);

		long long soma = 0;
		for (int i = 0; i < n; i++)
			if (mask&(1<<i))
				soma += 1ll*h[i];

		if (soma >= H)
			ans = max(ans, dp[mask]);
	}

	if (ans == -inf)
		printf("Mark is too tall\n");
	else
		printf("%d\n", ans);
}
