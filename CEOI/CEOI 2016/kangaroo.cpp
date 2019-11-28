// CEOI 2016 - Kangaroo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;
const int mod = 1e9+7;

int n;
int cs, cf;

int dp[maxn][maxn];

int solve(int pos, int cc)
{
	if (pos == n+1 && cc != 1) return 0;
	if (pos == n+1) return 1;
	if (dp[pos][cc] != -1) return dp[pos][cc];

	int ans = 0;

	if (pos == cs || pos == cf)
	{
		ans = (ans + solve(pos+1, cc))%mod;
		ans = (ans + solve(pos+1, cc+1))%mod;
		return dp[pos][cc] = ans;
	}

	if (cc >= 2)
	{
		ans = (1ll*ans + 1ll*(cc-1)*solve(pos+1, cc+1))%mod;
		ans = (1ll*ans + 1ll*(cc-1)*solve(pos+1, cc-1))%mod;
	}

	if (pos < cs)
		ans = (1ll*ans + 1ll*solve(pos+1, cc+1))%mod;

	if (pos < cf)
		ans = (1ll*ans + 1ll*solve(pos+1, cc+1))%mod;

	return dp[pos][cc] = ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &cs, &cf);

	if (cs > cf) swap(cs, cf);

	memset(dp, -1, sizeof dp);

	printf("%d\n", solve(2, 1));
}
