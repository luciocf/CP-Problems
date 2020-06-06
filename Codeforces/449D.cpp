// Codeforces 449D - Jzzhu and Numbers
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6+10;
const int mod = 1e9+7;

int pot[maxn];
int f[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	pot[0] = 1;
	for (int i = 1; i < maxn; i++)
		pot[i] = (2ll*pot[i-1])%mod;

	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);

		f[a]++;
	}

	for (int i = 0; i < 20; i++)
		for (int mask = (1<<20)-1; mask >= 0; mask--)
			if (!(mask&(1<<i)))
				f[mask] += f[mask|(1<<i)];

	int ans = 0;

	for (int mask = 0; mask < (1<<20); mask++)
	{
		int sz = __builtin_popcount(mask);
		int a = pot[f[mask]];

		if (sz%2) ans = (ans - a + mod)%mod;
		else ans = (ans + a)%mod;
	}

	printf("%d\n", ans);
}
