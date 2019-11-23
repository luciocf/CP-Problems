// Seletiva IOI 2014 - Inversor
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

int a[maxn];

ll pref[maxn];

ll dp[maxn][2];

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[i] = -a[i];

		pref[i] = pref[i-1]+1ll*a[i];
	}

	for (int i = 1; i < k; i++)
		dp[i][0] = -inf;
	for (int i = n-k+2; i <= n; i++)
		dp[i][1] = -inf;

	dp[k][0] = pref[k];
	for (int i = k+1; i <= n; i++)
		dp[i][0] = max(dp[i-1][0], pref[i]-pref[i-k]);

	dp[n-k+1][1] = pref[n]-pref[n-k];
	for (int i = n-k; i >= 1; i--)
		dp[i][1] = max(dp[i+1][1], pref[i+k-1]-pref[i-1]);

	ll ans = -inf;
	for (int i = 1; i < n; i++)
		ans = max(ans, dp[i][0]+dp[i+1][1]);

	printf("%lld\n", ans);
}
