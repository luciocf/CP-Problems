// Codeforces 451E - Devu and Flowers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9+7; 

int fat[22];
ll a[22];
 
int pot(int a, int b)
{
	if (!b) return 1;
 
	int t = pot(a, b/2);
 
	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}
 
int choose(ll a, int b)
{
	ll ans = 1;

	for (ll i = a; i > a-b; i--)
		ans = (ans*(i%mod))%mod;

	return (ans * 1ll*pot(fat[b], mod-2))%mod;
}
 
int main(void)
{
	int n;
	ll s;
	scanf("%d %lld", &n, &s);
 
	fat[0] = 1;
	for (int i = 1; i <= n; i++)
		fat[i] = (1ll*fat[i-1]*i)%mod;

	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);

	int ans = 0;

	for (int mask = 0; mask < (1<<n); mask++)
	{
		ll soma = s;

		for (int i = 0; i < n; i++)
			if (mask&(1<<i))
				soma -= (a[i]+1);

		if (soma < 0) continue;

		int x = choose(soma+1ll*n-1ll, n-1);

		if (__builtin_popcount(mask)%2) ans = (ans - x + mod)%mod;
		else ans = (ans + x)%mod;
	}

	printf("%d\n", ans);
}
