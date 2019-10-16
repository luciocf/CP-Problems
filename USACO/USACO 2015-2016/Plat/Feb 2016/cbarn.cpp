// USACO 2015/2016 - Circular Barn
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e3+10;
const ll inf = 1e18+10;

int n, k;
int v[maxn], a[maxn];
int s[maxn];

ll dp[maxn][8];

int opt[maxn];

void solve(int l, int r, int t)
{
	if (l > r) return;

	int mid = (l+r)>>1;

	for (int i = opt[l-1]; i <= min(mid-1, opt[r+1]); i++)
	{
		if (dp[i][t-1] + 1ll*i*(s[mid-1]-s[i-1]) > dp[mid][t])
		{
			dp[mid][t] = dp[i][t-1] + 1ll*i*(s[mid-1]-s[i-1]);
			opt[mid] = i;
		}
	}

	solve(l, mid-1, t); solve(mid+1, r, t);
}

int main(void)
{
	freopen("cbarn.in", "r", stdin);
	freopen("cbarn.out", "w", stdout);

	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &v[i]);

	ll ans = inf;

	for (int p = 1; p <= n; p++)
	{
		for (int i = 0; i < n; i++)
		{
			int x = (p+i)%n;
			if (x == 0) x = n;

			a[i+1] = v[x];
		}
		
		for (int i = 1; i <= n; i++)
			s[i] = s[i-1]+a[i];

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= k; j++)
				dp[i][j] = -inf;

		opt[0] = 1, opt[n+1] = n;
		dp[1][1] = 0;

		for (int i = 2; i <= k; i++)
			solve(1, n, i);

		ll P = 0;
		for (int i = 1; i <= n; i++)
			P += 1ll*a[i]*i;

		ll at = -inf;
		for (int i = 1; i <= n; i++)
			at = max(at, dp[i][k] + 1ll*i*(s[n]-s[i-1]));

		ans = min(ans, P-at);
	}

	printf("%lld\n", ans);
}
