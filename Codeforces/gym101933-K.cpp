// NCPC 2018 - K - King's Colors
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2510;
const int mod = 1e9+7;

int n, k;

int fat[maxn];
int inv[maxn];
 
int pot(int a, int b)
{
	if (!b) return 1;
 
	int t = pot(a, b/2);
 
	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}
 
int choose(int a, int b)
{
	return (1ll*fat[a]*((1ll*inv[a-b]*inv[b])%mod))%mod;
}

int f(int i)
{
	return (1ll*i*pot(i-1, n-1))%mod;
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);
	}

	fat[0] = inv[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		fat[i] = (1ll*i*fat[i-1])%mod;

		inv[i] = pot(fat[i], mod-2);
	}

	int ans = 0;
	int mult = 1;

	for (int i = k; i >= 1; i--)
	{
		int x = (1ll*f(i)*choose(k, i))%mod;

		ans = (1ll*ans + 1ll*mult*x + 1ll*mod)%mod;

		if (mult == 1) mult = -1;
		else mult = 1;
	}

	printf("%d\n", ans);
}
