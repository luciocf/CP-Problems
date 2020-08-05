// 2018-2019 XIX Open Cup, Grand Prix of Korea - G - Fascination Street
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;
const ll inf = 1e18+10;

int n, k;
int num[maxn];

ll dp[maxn][3][10][10];

ll solve(int i, int zero, int a, int b)
{
	if (i == 3 && zero == 2) return inf;
	if (i == n+1 && zero == 2) return inf;
	if (i == n+1 && a == b) return 0;
	if (i == n+1) return inf;
	if (dp[i][zero][a][b] != -1) return dp[i][zero][a][b];

	ll ans = inf;

	if (zero < 2) ans = min(ans, solve(i+1, zero+1, a, b));
	if (zero < 2 && a+1 <= k) ans = min(ans, 1ll*num[i] + solve(i+1, zero+1, a+1, b));

	ans = min(ans, 1ll*num[i] + solve(i+1, 0, a, b));
	if (b+1 <= k) ans = min(ans, solve(i+1, 0, a, b+1));

	return dp[i][zero][a][b] = ans;
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);

	memset(dp, -1, sizeof dp);

	if (n == 1)
	{
		printf("%d\n", num[1]);
		return 0;
	}

	printf("%lld\n", solve(1, 0, 0, 0));
}
