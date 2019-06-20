// USACO Gold Jan 2019 - Cow Poetry
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;
const int mod = 1e9+7;

typedef long long ll;

int w[maxn], tipo[maxn];

int qtd[maxn];

ll dp[maxn], tot[maxn];

void add(ll &a, ll b)
{
	a = (a+b)%mod;
}

void mult(ll &a, ll b)
{
	a = (a*b)%mod;
}

ll pot(ll a, ll b)
{
	if (!b) return 1;

	ll t = pot(a, b/2);

	if (b&1) return (a*((t*t)%mod))%mod;
	return (t*t)%mod;
}

int main(void)
{
	FILE *fin = fopen("poetry.in", "r");
	FILE *fout = fopen("poetry.out", "w");

	int n, m, k;
	fscanf(fin, "%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d %d", &w[i], &tipo[i]);

	for (int i = 1; i <= m; i++)
	{
		char c;
		fscanf(fin, " %c", &c);

		qtd[c-'A']++;
	}

	dp[0] = 1;
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= n; j++)
			if (i >= w[j])
				add(dp[i], dp[i-w[j]]);

	for (int i = 1; i <= n; i++)
		add(tot[tipo[i]], dp[k-w[i]]);

	ll ans = 1;
	for (int i = 0; i < 26; i++)
	{
		if (qtd[i] == 0) 
			continue;

		ll aux = 0;
		for (int j = 1; j <= n; j++)
			add(aux, pot(tot[j], qtd[i]));

		mult(ans, aux);
	}

	fprintf(fout, "%lld\n", ans);
}
