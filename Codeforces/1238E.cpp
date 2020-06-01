// Codeforces 1238E - Keyboard Purchase
// Lúcio Cardoso

// Solution in O(m*2^m), explained here -> https://codeforces.com/blog/entry/70450?#comment-549236

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n, m;
char s[maxn];

int qtd[21][21], low[1<<20];

ll dp[1<<20];
ll soma[21][1<<20];

int main(void)
{
	scanf("%d %d %s", &n, &m, s);

	for (int i = 0; i < n; i++)
	{
		if (i > 0) qtd[(int)(s[i]-'a')][(int)(s[i-1]-'a')]++;
		if (i < n-1) qtd[(int)(s[i]-'a')][(int)(s[i+1]-'a')]++;	
	}

	for (int mask = 1; mask < (1<<m); mask++)
	{
		dp[mask] = 1e18;

		for (int i = 0; i < m; i++)
		{
			if (mask&(1<<i))
			{
				low[mask] = i;
				break;
			}
		}
	}

	for (int mask = 1; mask < (1<<m); mask++)
		for (int i = 0; i < m; i++)
			soma[i][mask] = soma[i][mask^(1<<low[mask])] + qtd[i][low[mask]];

	for (int mask = 1; mask < (1<<m); mask++)
	{
		int sz = __builtin_popcount(mask);

		for (int i = 0; i < m; i++)
		{
			if (!(mask&(1<<i))) continue;

			int mask2 = mask^(1<<i);
			int tot = (1<<m)-1;

			dp[mask] = min(dp[mask], 1ll*sz*(soma[i][mask2] - soma[i][tot^mask]) + dp[mask2]);
		}
	}

	printf("%lld\n", dp[(1<<m)-1]);
}
