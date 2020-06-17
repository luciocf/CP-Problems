// Codeforces 1110D - Jongmah
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int n, m;
int freq[maxn];

int dp[maxn][3][3];

int solve(int i, int q1, int q2)
{
	if (i == m+1) return 0;
	if (dp[i][q1][q2] != -1) return dp[i][q1][q2];

	int ans = 0;

	for (int q3 = 0; q3 <= min({2, freq[i+1], freq[i+2], freq[i]-q1-q2}); q3++)
		ans = max(ans, q1 + (freq[i] - q1 - q2 - q3)/3 + solve(i+1, q2, q3));

	return dp[i][q1][q2] = ans;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		freq[x]++;
	}

	memset(dp, -1, sizeof dp);
	printf("%d\n", solve(1, 0, 0));
}
