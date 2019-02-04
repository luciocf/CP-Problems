// Seletiva IOI 2017 - Equipe
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;

const int inf = 1e9+10;

int mask[2][maxn], dp[2][(1<<10)+10][(1<<10)+10];

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
	{
		int m;
		cin >> m;

		mask[0][i] = (1<<k)-1;

		for (int j = 1; j <= m; j++)
		{
			int x;
			cin >> x;
			x--;

			mask[1][i] |= (1<<x);
			mask[0][i] ^= (1<<x);
		}
	}

	for (int mask1 = 0; mask1 < 1<<k; mask1++)
		for (int mask2 = 0; mask2 < 1<<k; mask2++)
			dp[0][mask1][mask2] = dp[1][mask1][mask2] = inf;

	dp[0][0][0] = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int mask1 = 0; mask1 < 1<<k; mask1++)
		{
			for (int mask2 = 0; mask2 < 1<<k; mask2++)
			{
				int a = i%2, b = (i-1)%2;
				int new1 = mask1|mask[1][i];
				int new0 = mask2|mask[0][i];

				dp[a][new1][new0] = min({dp[a][mask1][mask2]+1, dp[a][new1][new0], dp[b][mask1][mask2]+1, dp[b][new1][new0]});
			}
		}
	}

	int ans = dp[n%2][(1<<k)-1][(1<<k)-1];
	cout << (ans==inf?-1:ans) << "\n";
}