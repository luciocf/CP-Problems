// Seletiva IOI 2015 - Serrote
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;
const int mod = 1e9+7;

int dp[maxn][maxn];

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	dp[1][0] = 1;

	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			dp[i][j] = (1ll*dp[i][j] + 1ll*dp[i-1][j]*(2*j+2))%mod;

			if (i >= 2*j+2) dp[i][j+1] = (1ll*dp[i][j+1] + 1ll*dp[i-1][j]*(i-2*j-2))%mod; 
		}
	}

	printf("%d\n", dp[n][k]);
}
