// CSES 1653 - Elevator Rides
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 20;
const int inf = 1e9+10;

int w[maxn];

pii dp[1<<maxn];

int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);

	for (int i = 0; i < n; i++)
		scanf("%d", &w[i]);

	dp[0] = {1, 0};

	for (int mask = 1; mask < (1<<n); mask++)
	{
		dp[mask] = {inf, inf};

		for (int i = 0; i < n; i++)
		{
			if (!(mask&(1<<i))) continue;

			int s = mask^(1<<i);

			if (dp[s].ss+w[i] > x)
			{
				if (dp[mask].ff > dp[s].ff+1 || (dp[mask].ff == dp[s].ff+1 && dp[mask].ss > w[i]))
				{
					dp[mask].ff = dp[s].ff+1;
					dp[mask].ss = w[i];
				}
			}
			else
			{
				if (dp[mask].ff > dp[s].ff || (dp[mask].ff == dp[s].ff && dp[mask].ss > dp[s].ss+w[i]))
				{
					dp[mask].ff = dp[s].ff;
					dp[mask].ss = dp[s].ss+w[i];
				}
			}
		}
	}

	printf("%d\n", dp[(1<<n)-1]);
}
