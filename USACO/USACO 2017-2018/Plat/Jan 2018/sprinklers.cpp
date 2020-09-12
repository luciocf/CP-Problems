// USACO 2017/2018 Platinum - Sprinklers
// Lúcio Cardoso

// Solution is the same as in: https://github.com/stefdasca/CompetitiveProgramming/blob/master/USACO/USACO%2018jan-sprinklers-plat.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e9+7;

int h[maxn];

int mn[maxn], mx[maxn];

int pref[2][maxn];

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;

	return (1ll*t*t)%mod;
}

int main(void)
{
	freopen("sprinklers.in", "r", stdin); freopen("sprinklers.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		++x, ++y;

		h[x] = y;
	}

	mn[1] = h[1];
	for (int i = 2; i <= n; i++)
		mn[i] = min(h[i], mn[i-1]);

	mx[n] = h[n];
	for (int i = n-1; i >= 1; i--)
		mx[i] = max(h[i], mx[i+1]);

	for (int i = 1; i <= n; i++)
	{
		pref[0][i] = (pref[0][i-1] + (1ll*mn[i]*mn[i])%mod)%mod;
		pref[1][i] = (pref[1][i-1] + mn[i])%mod;
	}

	int ans = 0, ptr = n;

	for (int i = n; i > 1; i--)
	{	
		ptr = min(ptr, i-1);
		while (ptr > 0 && mn[ptr] < mx[i])
			ptr--;

		ans = (ans + ((pref[0][i-1]-pref[0][ptr]+mod)%mod))%mod;

		ans = (ans - ((1ll*(2*mx[i]+1)*(pref[1][i-1]-pref[1][ptr]+mod))%mod) + mod)%mod;

		ans = (ans + (1ll*(i-ptr-1)*((1ll*(mx[i]+1)*mx[i])%mod))%mod)%mod;
	}

	printf("%d\n", (1ll*ans*pot(2, mod-2))%mod);
}
