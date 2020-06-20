// Codeforces 1336C - Kaavi and Magic Spell
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;
const int mod = 998244353;

int dp[maxn][maxn];

int main(void)
{
	string s, t;
	cin >> s >> t;

	int n = s.size(), m = t.size();

	dp[n][0] = 1;

	for (int i = n-1; i > 0; i--)
	{
		for (int j = 0; j <= m; j++)
		{
			if (j == 0)
			{
				if (i >= m) dp[i][j] = n-i+1;
				else if (s[i] == t[i]) dp[i][j] = dp[i+1][j];
			}
			else if (j == m)
			{
				dp[i][j] = (2*dp[i+1][m])%mod;

				if (s[i] == t[m-1]) dp[i][j] = (dp[i][j] + dp[i+1][j-1])%mod;
			}
			else
			{
				if (s[i] == t[j-1]) dp[i][j] = (dp[i][j] + dp[i+1][j-1])%mod;

				if (i + j >= m || s[i] == t[i+j]) dp[i][j] = (dp[i][j] + dp[i+1][j])%mod;
			}
		}
	}

	int ans = (2*dp[1][m])%mod;

	for (int i = 0; i < m; i++)
		if (s[0] == t[i])
			ans = (ans + (2*dp[1][i])%mod)%mod;

	printf("%d\n", ans);
}
