// Codeforces 839D - Winter is here
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int maxv = 1e6+10;
const int mod = 1e9+7;

int a[maxn];
int freq[maxv];

int pot[maxn];

int soma[maxv];

int f(int n)
{
	if (n == 0) return 0;

	assert(n < maxn);

	return (1ll*pot[n-1]*n)%mod;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	pot[0] = 1;
	for (int i = 1; i < maxn; i++)
		pot[i] = (2ll*pot[i-1])%mod;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		freq[a[i]]++;
	}

	int ans = 0;

	for (int d = maxv-1; d >= 2; d--)
	{
		int tot = 0;
		for (int j = d; j < maxv; j += d)
			tot += freq[j];

		int S = f(tot);

		for (int j = 2*d; j < maxv; j += d)
			S = (S - soma[j] + mod)%mod;

		soma[d] = S;
		ans = (1ll*ans + 1ll*soma[d]*d)%mod;
	}

	printf("%d\n", ans);
}
