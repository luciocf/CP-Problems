// Codeforces 1216F - Wi-Fi
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
 
struct Segment
{
	int l, r, ind;
} range[maxn];
 
ll dp[maxn], pref[maxn];
 
int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
 
	int m = 0;
 
	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);
 
		if (c == '1') range[++m] = {max(1, i-k), min(n, i+k), i};
	}
 
	if (m == 0)
	{
		printf("%lld\n", 1ll*n*(n+1)/2ll);
		return 0;
	}
 
	for (int i = 1; i <= m; i++)
	{
		int ini = 1, fim = i, x;
 
		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;
 
			if (range[mid].r >= range[i].l-1) x = mid, fim = mid-1;
			else ini = mid+1;
		}
 
		ll interv = 1ll*range[i].l*(range[i].l-1)/2ll - 1ll*range[i].r*(range[i].r+1)/2ll;
		ll caso1 = range[i].ind + interv + pref[x-1];
 
		interv = 1ll*range[x].r*(range[x].r+1)/2ll - 1ll*range[i].r*(range[i].r+1)/2ll;
		ll caso2 = (x == i ? 1e18 : 1ll*range[i].ind + interv + dp[x]);
 
		dp[i] = min(caso1, caso2);
		pref[i] = min(pref[i-1], dp[i]);
	}
 
	ll ans = 1e18+10;
 
	for (int i = 1; i <= m; i++)
		ans = min(ans, dp[i] + 1ll*n*(n+1)/2ll);
 
	printf("%lld\n", ans);
}
