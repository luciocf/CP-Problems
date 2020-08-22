// Codeforces 1228E - Another Filling the Grid
// Lúcio Cardoso

// Solution is the same as in editorial (in O(n log n)).

#include <bits/stdc++.h>

using namespace std;
 
const int mod = 1e9+7;

int fat[500];

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
	int n, k;
	scanf("%d %d", &n, &k);

	fat[0] = 1;
	for (int i = 1; i <= n; i++)
		fat[i] = (1ll*fat[i-1]*i)%mod;

	int ans = 0;

	for (int i = 0; i <= n; i++)
	{
		int c = choose(n, i);

		int a = (1ll*pot(k-1, i)*pot(k, n-i))%mod;
		int b = pot(k-1, n);

		int x = pot((a-b+mod)%mod, n);

		if (i%2) ans = (ans - (1ll*x*c)%mod + mod)%mod;
		else ans = (ans + (1ll*x*c)%mod)%mod;

	}

	printf("%d\n", ans);
}
