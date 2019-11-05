// Seletiva IOI 2017 - Equipe
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;
const int inf = 1e9+10;

int in[maxn], out[maxn];

int dp[2][(1<<11)][(1<<11)];

vector<int> tema[maxn];

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		int m;
		scanf("%d", &m);

		for (int j = 1; j <= m; j++)
		{
			int t;
			scanf("%d", &t);

			in[i] |= (1<<(t-1));
		}

		for (int j = 0; j < k; j++)
			if (!(in[i]&(1<<j)))
				out[i] |= (1<<j);
	}

	for (int mask1 = 0; mask1 < (1<<k); mask1++)
		for (int mask2 = 0; mask2 < (1<<k); mask2++)
			dp[0][mask1][mask2] = dp[1][mask1][mask2] = inf;

	dp[0][0][0] = dp[1][0][0] = 0;

	for (int i = 1; i <= n; i++)
	{
		int at = i%2, ant = (i-1)%2;

		for (int mask1 = 0; mask1 < (1<<k); mask1++)
		{
			for (int mask2 = 0; mask2 < (1<<k); mask2++)
			{
				dp[at][mask1][mask2] = min(dp[at][mask1][mask2], dp[ant][mask1][mask2]);

				int m1 = mask1|in[i], m2 = mask2|out[i];

				dp[at][m1][m2] = min({dp[at][m1][m2], dp[ant][m1][m2], dp[ant][mask1][mask2]+1});
			}
		}

	}

	if (dp[n%2][(1<<k)-1][(1<<k)-1] == inf) printf("-1\n");
	else printf("%d\n", dp[n%2][(1<<k)-1][(1<<k)-1]);
}
