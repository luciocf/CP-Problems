// Codeforces 1312E - Array Shrinking
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;
const int inf = 1e9+10;

int n;
int a[maxn];

int dp1[maxn][maxn], dp2[maxn][maxn];

int solve1(int l, int r)
{
	if (l == r) return dp1[l][r] = a[l];
	if (l > r) return dp1[l][r] = 0;
	if (dp1[l][r] != -1) return dp1[l][r];

	int ans = 0;

	for (int i = l; i < r; i++)
	{
		solve1(l, i); solve1(i+1, r);

		if (dp1[l][i] != 0 && dp1[i+1][r] != 0 && (dp1[l][i] == dp1[i+1][r]))
			ans = dp1[l][i]+1;
	}

	return dp1[l][r] = ans;
}

int solve2(int l, int r)
{
	if (l > r) return inf;
	if (l == r || dp1[l][r] > 0) return 0;
	if (dp2[l][r] != -1) return dp2[l][r];

	int ans = inf;

	for (int i = l; i < r; i++)
		ans = min(ans, 1+solve2(l, i)+solve2(i+1, r));

	return dp2[l][r] = ans;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	memset(dp1, -1, sizeof dp1);
	memset(dp2, -1, sizeof dp2);

	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++)
			solve1(l, r);

	printf("%d\n", solve2(1, n)+1);
}
