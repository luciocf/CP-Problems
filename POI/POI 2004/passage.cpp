// POI 2004 - Passage
// Lúcio Cardoso

// Solution:

// Let's use dp to solve the problem. Define dp[mask] as the minimum time for every people in the bitmask "mask"
// to pass the bridge. Also, for every mask, precalculate in O(2^n * n) the sum of weights in that mask and
// the time of the slowest person in such mask.

// The transition for the dp is: dp[mask] = min(time[sub] + dp[mask^sub]), where "sub" is a submask of "mask" such that
// the sum of weights in "sub" is <= w. Essentialy, "sub" defines the next group that's going to cross the bridge.

// Since for every mask we iterate through all of its submasks, the complexity is O(sum(0 <= i <= n) 2^i * (n choose i)),
// (there are (n choose i) masks of size i and each of them has 2^i submasks), and this summation is equal to 3^n by the
// binomial theorem. Hence, complexity is O(3^n).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;
const int inf = 1e9+10;

int n, m;
int t[maxn], w[maxn];

int peso[1<<maxn], tempo[1<<maxn];
int dp[1<<maxn];

void calc(void)
{
	for (int mask = 0; mask < (1<<n); mask++)
	{
		for (int i = 0; i < n; i++)
		{
			if (mask&(1<<i))
			{
				peso[mask] += w[i];
				tempo[mask] = max(tempo[mask], t[i]);
			}
		}
	}
}

int solve(int mask)
{
	if (mask == 0) return 0;
	if (dp[mask] != -1) return dp[mask];

	int ans = inf;
	for (int sub = mask; sub > 0; sub = (sub-1)&mask)
		if (peso[sub] <= m)
			ans = min(ans, tempo[sub] + solve(mask^sub));

	return dp[mask] = ans;
}

int main(void)
{
	scanf("%d %d", &m, &n);

	for (int i = 0; i < n; i++)
		scanf("%d %d", &t[i], &w[i]);

	calc();

	memset(dp, -1, sizeof dp);

	printf("%d\n", solve((1<<n)-1));
}
