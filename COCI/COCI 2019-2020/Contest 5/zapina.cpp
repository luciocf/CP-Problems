// COCI 2019/2020 - Zapina
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 705;
const int mod = 1e9+7;

int n;
int dp[maxn][maxn];

int choose[maxn][maxn];
int fat[maxn];

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}

void calc(void)
{
	for (int i = 1; i <= n; i++)
	{
		choose[i][0] = 1;

		for (int j = 1; j <= i; j++)
			choose[i][j] = (((1ll*choose[i][j-1]*(i-j+1))%mod)*pot(j, mod-2))%mod;
	}
}

int main(void)
{
	scanf("%d", &n);

	calc();

	for (int i = 0; i <= n; i++)
		dp[i][0] = 1;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int l = 0; l <= j; l++)
				if (l != i)
					dp[i][j] = (1ll*dp[i][j] + (1ll*choose[j][l]*dp[i-1][j-l]))%mod;

	printf("%d\n", ((pot(n, n) + (mod-dp[n][n]))%mod));
}
