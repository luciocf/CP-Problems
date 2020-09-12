// ACM-ICPC Latin American Regional Programming Contest 2019 - F - Fabricating Sculptures
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;
const int mod = 1e9+7;

int dp[maxn][maxn];

int pref[2][maxn][maxn];

int main(void)
{
	int s, b;
	scanf("%d %d", &s, &b);

	for (int i = 0; i <= s; i++)
	{
		dp[0][i] = 1;

		pref[0][0][i] = 1, pref[1][0][i] = i;
	}

	for (int i = 1; i <= b-s; i++)
	{
		for (int j = 0; j <= s; j++)
		{
			int a = (pref[0][i-1][1] - (i <= j ? 0 : pref[0][i-(j+1)][j+1]) + mod)%mod;
			int b = (pref[1][i-1][1] - (i <= j ? 0 : pref[1][i-(j+1)][j+1]) + mod)%mod;

			dp[i][j] = ((1ll*(j+1)*a)%mod - b + mod)%mod;

			pref[0][i][j] = (pref[0][i-1][j+1] + dp[i][j])%mod;

			pref[1][i][j] = (pref[1][i-1][j+1] + (1ll*j*dp[i][j])%mod)%mod;
		}
	}

	printf("%d\n", dp[b-s][s]);
}
