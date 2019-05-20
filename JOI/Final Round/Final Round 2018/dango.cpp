// JOI Final Round 2018 - Dango Maker
// Lúcio Cardoso

// Idea is explained here: https://codeforces.com/blog/entry/57637?#comment-413356

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e3+10;

int n, m;
int dp[3][maxn][maxn];

// ans[k] -> maximum possible amount of 'G's on diagonal with sum K
int ans[2*maxn];

bool h[maxn][maxn], v[maxn][maxn];

char tab[maxn][maxn];

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (tab[i][j] == 'G')
			{
				if (j < m && j > 1 && tab[i][j-1] == 'R' && tab[i][j+1] == 'W')
					h[i][j] = 1;

				if (i < n && i > 1 && tab[i-1][j] == 'R' && tab[i+1][j] == 'W')
					v[i][j] = 1;
			}
		}
	}

	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j <= m; j++)
		{
			dp[0][i][j] = max({dp[0][i+1][j-1], dp[1][i+1][j-1], dp[2][i+1][j-1]});

			if (h[i][j])
				dp[1][i][j] = 1+max(dp[0][i+1][j-1], dp[1][i+1][j-1]);

			if (v[i][j])
				dp[2][i][j] = 1+max(dp[0][i+1][j-1], dp[2][i+1][j-1]);

			ans[i+j] = max({ans[i+j], dp[0][i][j], dp[1][i][j], dp[2][i][j]});
		}
	}

	int tot = 0;
	for (int i = 1; i <= n+m; i++)
		tot += ans[i];

	printf("%d\n", tot);
}
