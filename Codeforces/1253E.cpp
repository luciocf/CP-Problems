// Codeforces 1253E - Antenna Coverage
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int l[maxn], r[maxn];
int dp[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int mn = m+1;

	for (int i = 1; i <= n; i++)
	{
		int x, s;
		scanf("%d %d", &x, &s);

		l[i] = max(1, x-s), r[i] = min(m, x+s);
		mn = min(mn, l[i]);
	}

	for (int i = mn; i <= m; i++)
	{
		dp[i] = inf;

		for (int j = 1; j <= n; j++)
		{
			if (i >= l[j] && i <= r[j])
			{
				if (i > mn) dp[i] = min(dp[i], dp[i-1]);
				else dp[i] = min(dp[i], mn-1);
			}
		}

		for (int j = 1; j <= n; j++)
		{
			if (i > r[j])
			{
				int add = ((l[j]-i+r[j]-1 < mn && l[j]-i+r[j]-1 >= 1) ? l[j]-i+r[j]-1 : 0);

				dp[i] = min(dp[i], i-r[j] + dp[max(0, l[j]-i+r[j]-1)]+add);
			}
		}
	}

	printf("%d\n", dp[m]);
}
