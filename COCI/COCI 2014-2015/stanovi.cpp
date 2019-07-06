// COCI 2014/2015 - Stanovi
// Lúcio Cardoso

// Solution is the same as this one: http://hsin.hr/coci/archive/2014_2015/ (Contest #4)

// Essentialy, it's possible to prove that you can split the grid in a vertical or horizontal line
// and recursively solve for both parts. This results in an O(n^3 * 2^4) dp.
// 2^4 state is stored to maintain the amount of sides of the grid shared.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;
const long long inf = 2e18+10;

typedef long long ll;

int n, m, k;

ll dp[maxn][maxn][2][2][2][2];

ll solve(int a, int b, int l, int r, int u, int d)
{
	if (!(l || r || u || d)) return inf;

	// some constant optimizations here
	if (dp[a][b][l][r][u][d] != -1) return dp[a][b][l][r][u][d];
	if (dp[b][a][u][d][r][l] != -1) return dp[a][b][l][r][u][d] = dp[b][a][u][d][r][l];
	if (dp[a][b][r][l][u][d] != -1) return dp[a][b][l][r][u][d] = dp[a][b][r][l][u][d];
	if (dp[a][b][l][r][d][u] != -1) return dp[a][b][l][r][u][d] = dp[a][b][l][r][d][u];

	ll ans = (1ll*a*b - 1ll*k)*(1ll*a*b - 1ll*k);

	if (u || d || (l && r))
		for (int i = 1; i < a; i++)
			ans = min(ans, solve(i, b, l, 0, u, d) + solve(a-i, b, 0, r, u, d));

	if (l || r || (u && d))
		for (int i = 1; i < b; i++)
			ans = min(ans, solve(a, i, l, r, u, 0) + solve(a, b-i, l, r, 0, d));

	return dp[a][b][l][r][u][d] = ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	memset(dp, -1, sizeof dp);

	printf("%lld\n", solve(n, m, 1, 1, 1, 1));
}
