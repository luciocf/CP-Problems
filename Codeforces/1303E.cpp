// Codeforces 1303E - Erase Subsequences
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 410;
const int inf = 1e9;

int dp[maxn][maxn];

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		string s, p;
		cin >> s >> p;

		int n = s.size(), m = p.size();

		bool ok = 0;

		for (int a = 0; a <= m; a++)
		{
			for (int i = 0; i <= n; i++)
				for (int j = 1; j <= m; j++)
					dp[i][j] = -inf;

			for (int i = 0; i <= n; i++)
				dp[i][0] = 0;

			for (int i = 1; i <= n; i++)
			{
				for (int j = 0; j <= a; j++)
				{
					dp[i][j] = dp[i-1][j];

					if (dp[i-1][j] >= 0 && s[i-1] == p[a + dp[i-1][j]])
						dp[i][j] = max(dp[i][j], dp[i-1][j]+1);

					if (j > 0 && s[i-1] == p[j-1])
						dp[i][j] = max(dp[i][j], dp[i-1][j-1]);
				}
			}

			if (dp[n][a] >= m-a)
			{
				ok = 1;
				break;
			}
		}

		if (ok) printf("YES\n");
		else printf("NO\n");
	}
}
