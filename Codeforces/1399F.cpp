// Codeforces 1399F - Yet Another Segments Subset
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 6e3+10;

int n;
pii range[maxn];

int dp[maxn][maxn];

vector<int> ind[maxn];

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[range[i].ff] = mp[range[i].ss] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		range[i].ff = mp[range[i].ff];
		range[i].ss = mp[range[i].ss];
	}
}

void solve(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= 2*n; i++)
	{
		for (int j = 1; j <= 2*n; j++)
			dp[i][j] = 0;

		ind[i].clear();
	}

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &range[i].ff, &range[i].ss);

	compress();

	for (int i = 1; i <= n; i++)
		ind[range[i].ff].push_back(i);

	int ans = 0;

	for (int r = 1; r <= 2*n; r++)
	{
		for (int l = r; l >= 1; l--)
		{
			int add = 0;
			for (auto i: ind[l])
				if (range[i].ss == r)
					add = 1;

			dp[l][r] = max(dp[l][r], add+dp[l+1][r]);

			for (auto i: ind[l])
			{
				int b = range[i].ss;
				if (b >= r) continue;

				dp[l][r] = max(dp[l][r], add + dp[l][b]	+ dp[b+1][r]);
			}

			ans = max(ans, dp[l][r]);
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--) solve();
}
