// USACO 2017/2018 Platinum - Lifeguards
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;
const int inf = 2e9+10;

int n, k;
pii range[maxn];

bool mark[maxn];

vector<pii> good;

int dp[maxn][110];

void get(void)
{
	int mx = 0;

	for (int i = 1; i <= n; i++)
	{
		int j;
		for (j = i; j <= n && range[j].ff == range[i].ff; j++)
			;
		j--;

		if (mx >= range[j].ss) mark[j] = 1;

		for (int l = i; l < j; l++)
			mark[l] = 1;

		mx = max(mx, range[j].ss);
		i = j;
	}
}

int main(void)
{
	freopen("lifeguards.in", "r", stdin); freopen("lifeguards.out", "w", stdout);

	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &range[i].ff, &range[i].ss);

	sort(range+1, range+n+1);

	get();

	int t = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!mark[i]) good.push_back(range[i]);
		else t++;
	}

	for (int i = 0; i < good.size(); i++)
		for (int j = 0; j <= k; j++)
			dp[i][j] = -inf;

	int l = 0;
	for (int r = 0; r < good.size(); r++)
	{
		while (good[l].ss < good[r].ff)
			++l;

		for (int j = 0; j <= min(k, r+1); j++)
		{
			if (r == 0)
			{
				if (j == 0) dp[r][j] = good[r].ss-good[r].ff;
				else dp[r][j] = 0;
				continue;
			}

			if (j) dp[r][j] = max(dp[r][j], dp[r-1][j-1]);

			if (l != r && j >= r-l-1) dp[r][j] = max(dp[r][j], good[r].ss-good[l].ss + dp[l][j - (r-l-1)]);

			if (l && j >= r-l) dp[r][j] = max(dp[r][j], good[r].ss-good[r].ff + dp[l-1][j - (r-l)]);
			if (!l && j == r-l) dp[r][j] = max(dp[r][j], good[r].ss-good[r].ff);
		}
	}

	int ans = 0;

	printf("%d\n", dp[good.size()-1][max(0, k-t)]);
}
