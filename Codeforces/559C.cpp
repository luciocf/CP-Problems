// Codeforces 559C - Gerald and Giant Chess
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;
const int mod = 1e9+7;

int fat[maxn];

pii pt[maxn];

int dp[maxn];

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b%2) return (1ll*a*((1ll*t*t)%mod))%mod;

	return (1ll*t*t)%mod;
}

int choose(int a, int b)
{
	return (1ll*fat[a]*pot((1ll*fat[b]*fat[a-b])%mod, mod-2))%mod;
}

int main(void)
{
	int h, w, n;
	scanf("%d %d %d", &h, &w, &n);

	fat[0] = 1;
	for (int i = 1; i < maxn; i++)
		fat[i] = (1ll*i*fat[i-1])%mod;

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &pt[i].ff, &pt[i].ss);

	sort(pt+1, pt+n+1);

	for (int i = 1; i <= n; i++)
	{
		dp[i] = choose(pt[i].ff+pt[i].ss-2, pt[i].ff-1);

		for (int j = 1; j < i; j++)
		{
			int a = dp[j];
			int b = choose(pt[i].ff+pt[i].ss-pt[j].ff-pt[j].ss, pt[i].ff-pt[j].ff);

			dp[i] = (dp[i] - (1ll*a*b)%mod + mod)%mod;
		}
	}

	int ans = choose(h+w-2, h-1);

	for (int i = 1; i <= n; i++)
	{
		if (pt[i].ff > h || pt[i].ss > w) continue;

		int a = dp[i];
		int b = choose(h+w-pt[i].ff-pt[i].ss, h-pt[i].ff);

		ans = (ans - (1ll*a*b)%mod + mod)%mod;
	}

	printf("%d\n", ans);
}
