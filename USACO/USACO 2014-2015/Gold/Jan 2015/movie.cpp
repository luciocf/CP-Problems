// USACO Gold Jan 2015 - Moovie Mooving
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 21;

int dp[1<<maxn];

int delta[maxn];

vector<int> C[maxn];

int main(void)
{
	freopen("movie.in", "r", stdin);
	freopen("movie.out", "w", stdout);

	int n, L;
	scanf("%d %d", &n, &L);

	for (int i = 0; i < n; i++)
	{
		int m;
		scanf("%d %d", &delta[i], &m);

		for (int j = 0; j < m; j++)
		{
			int t;
			scanf("%d", &t);

			C[i].push_back(t);
		}
	}

	for (int mask = 1; mask < (1<<n); mask++)
	{
		for (int i = 0; i < n; i++)
		{
			if (!(mask&(1<<i))) continue;

			int mask2 = mask^(1<<i);
			int T = dp[mask2];

			auto it = upper_bound(C[i].begin(), C[i].end(), dp[mask2]);

			if (it == C[i].begin()) continue;

			--it;

			if (*it > T+delta[i]) continue;

			dp[mask] = max(dp[mask], *it+delta[i]);
		}
	}

	int ans = n+1;

	for (int mask = 1; mask < (1<<n); mask++)
		if (dp[mask] >= L)
			ans = min(ans, __builtin_popcount(mask));

	if (ans == n+1) printf("-1\n");
	else printf("%d\n", ans);
}
