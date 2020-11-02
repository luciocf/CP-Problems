// NWERC 2015 - Debugging - D
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;
const ll inf = 1e18+10;

int n, r, p;
ll dp[maxn];

ll solve(int x)
{
	if (x <= 1) return 0;
	if (dp[x] != -1) return dp[x];

	ll ans = 1ll*r + 1ll*(x-1)*p;

	for (int k = 2; k < x; )
	{
		int f = x/k, c = (x+k-1)/k;

		ans = min(ans, 1ll*r + 1ll*(k-1)*p + solve(c));

		k = x/f + 1;
	}

	return dp[x] = ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &r, &p);

	memset(dp, -1, sizeof dp);
	printf("%lld\n", solve(n));
}
