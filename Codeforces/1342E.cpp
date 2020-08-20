// Codeforces 1342E - Placing Rooks
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int mod = 998244353;

int fat[maxn];

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}

int choose(int a, int b)
{
	return (1ll*fat[a] * pot((1ll*fat[b]*fat[a-b])%mod, mod-2))%mod;
}

int main(void)
{
	int n;
	long long k;
	scanf("%d %lld", &n, &k);

	if (k >= n)
	{
		printf("0\n");
		return 0;
	}

	fat[0] = 1;
	for (int i = 1; i <= n; i++)
		fat[i] = (1ll*fat[i-1]*i)%mod;

	int soma = 0;

	for (int i = 0; i <= n-k; i++)
	{
		int a = choose(n-k, i);
		int b = pot(n-k-i, n);

		if (i%2) soma = (1ll*soma - (1ll*a*b)%mod + mod)%mod;
		else soma = (1ll*soma + (1ll*a*b)%mod)%mod;
	}

	int ans = (1ll*soma*choose(n, k))%mod;

	if (k == 0) printf("%d\n", ans);
	else printf("%d\n", (2ll*ans)%mod);
}
