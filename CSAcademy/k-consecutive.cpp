// CS Academy - K-Consecutive
// Lúcio Cardoso

// Solution is the same as the editorial: https://csacademy.com/contest/ioi-2016-training-round-4/task/k-consecutive/statement/

// For a little bit more of detail, the transitions for each case while calculating dp[i][j] are:

//	* dp[i][j] += (j+1)*dp[i-1][j+1] (this means we added 'i' in the middle of two consecutive numbers, thus decreasing the amount of consec. numbers by 1)

//	* dp[i][j] += dp[i-1][j-1] (this means we added 'i' straight after 'i-1', thus increasing by 1 the amount of consecutive pairs of numbers in the permutation)

//	* dp[i][j] += dp[i-1][j] (this is the remaining case, inserting 'i' in any position except the ones above. Since j of them are in the middle of a pair of consec.
//                            numbers and one of them is right after 'i-1', there are (i-j-1) in this last case, and inserting 'i' in any of them does not change the
//                            the amount of consecutive pairs)

// After this, dp2[i][j] is the 'perm[i][j]' in the editorial and 'soma[i][j]' is the prefix sum in such dp.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3+10;
const int mod = 1e9+7;

int n, k;

int dp[maxn][maxn];

int dp2[maxn][maxn];
int soma[maxn][maxn];

int main(void)
{
	scanf("%d %d", &n, &k);

	dp[1][0] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int a = (1ll*(j+1)*dp[i-1][j+1])%mod;
			int b = (j > 0 ? dp[i-1][j-1] : 0);
			int c = (1ll*(i-j-1)*dp[i-1][j])%mod;

			dp[i][j] = ((a + b)%mod + c)%mod;
		}
	}

	for (int i = 0; i <= n; i++)
		soma[i][0] = 1;

	for (int j = 1; j <= n; j++)
	{
		dp2[j][j] = 1;

		for (int i = j+1; i <= n; i++)
			dp2[i][j] = (soma[i-1][j-1] - (i-k >= 1 ? soma[i-k-1][j-1] : 0) + mod)%mod;

		for (int i = j; i <= n; i++)
			soma[i][j] = (soma[i-1][j]+dp2[i][j])%mod;
	}

	int ans = 0;
	for (int j = 1; j <= n; j++)
		ans = (ans + (1ll*dp2[n][j]*dp[j][0])%mod)%mod;

	printf("%d\n", ans);
}
