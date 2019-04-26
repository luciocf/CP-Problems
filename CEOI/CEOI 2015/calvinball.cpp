// CEOI 2015 - Calvinball Championship
// Lúcio Cardoso

// Solution:
/*

1. Define mx[i] as the maximum team number from 1 to i. Also, define qtd[i][j] as the amount of configurations
of teams with i people and assuming the captain of all teams from 1 until j has already been chosen.

2. Notice the position of a given team configuration T is the following sum, for each index i:

qtd[n-i][max(mx[i-1], a[i]-1)] + qtd[n-i][max(mx[i-1], a[i]-2)] + ... + qtd[n-i][max(mx[i-1], 1)].

Basically, we count the amount of configurations P with a position smaller than T. If, in P, all team values before position
i are equal to the ones on T and P[i] < T[i], the subsequent values don't matter, because P already comes before T (as long as the
next values form a valid team config.). Hence, the sum above.

3. The problem becomes calculating qtd efficiently. We can use DP for that, with the same states in qtd. So we have that:

dp[i][j] = j*dp[i-1][j] + dp[i-1][j+1].

That is, we can either choose a number not greater than j in the first of the i positions, or choose j+1. So, we can calculate that in O(n^2).

4. However, the size of the DP table is way too large for full points. To improve it, notice that while calculating the sum 
in (2) for an index i, the DPs with first state greater than n-i will never be used again. So, we can calculate the sums
going backwards (from n until 1) and, at the same time, calculate dp[n-i][]. This way, the first state will be increasing, 
starting from 0. Since we only need dp[i+1][] to calculate dp[i][j], we can use the memory trick, using only the current and previous state in the dp.

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;
const int mod = 1e6+7;

int a[maxn];

int dp[2][maxn], mx[maxn];

void add(int &a, int b)
{
	a = (a+b)%mod;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		mx[i] = max(mx[i-1], a[i]);
	}

	for (int i = 1; i <= n; i++) dp[0][i] = 1;

	int ans = 1;
	for (int i = n-1; i >= 1; i--)
	{
		int cur = (n-i)%2, prev = (n-i-1)%2;

		for (int j = 1; j <= n; j++)
		{
			dp[cur][j] = 0;

			add(dp[cur][j], (1ll*j*dp[prev][j])%mod);
			add(dp[cur][j], dp[prev][j+1]);
		}


		for (int j = a[i]-1; j >= 1; j--)
			add(ans, dp[cur][max(mx[i-1], j)]);
	}

	add(ans, a[n]-1);

	printf("%d\n", ans);
}
