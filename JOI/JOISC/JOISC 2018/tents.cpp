// JOI Spring Camp 2018 - Tents
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;
const long long mod = 1e9+7;

typedef long long ll;

ll dp[maxn][maxn];

int main(void)
{
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < maxn; i++)
		dp[i][0] = dp[0][i] = 1LL;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			dp[i][j] = dp[i-1][j];

			dp[i][j] = (dp[i][j] + (dp[i-1][j-1]*4LL*(ll)j))%mod;

			if (j >= 2) 
				dp[i][j] = (dp[i][j] + (dp[i-1][j-2] * 1LL*(j*(j-1))/2))%mod;

			if (i >= 2) 
				dp[i][j] = (dp[i][j] + (dp[i-2][j-1] * 1LL*(j*(i-1))))%mod;
		}
	}

	cout << dp[n][m]-1LL << "\n";
}
