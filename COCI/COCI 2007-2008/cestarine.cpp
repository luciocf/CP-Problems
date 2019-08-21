// COCI 2007/2008 - Cestarine
// Lúcio Cardoso

// Solution: http://hsin.hr/coci/archive/2007_2008/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

int n;
int a[maxn], b[maxn];

ll dp[maxn];

ll cost(int l, int r)
{
	vector<int> c, d;

	for (int i = l; i <= r; i++)
	{
		c.push_back(a[i]);
		d.push_back(b[i]);
	}

	sort(c.begin(), c.end());

	ll ans = inf;
	do
	{
		ll tot = 0;

		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] == d[i])
			{
				tot = inf;
				break;
			}

			tot += 1ll*abs(c[i]-d[i]);
		}

		ans = min(ans, tot);
	} while (next_permutation(c.begin(), c.end()));

	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		scanf("%d", &b[i]);
	}

	sort(a+1, a+n+1); sort(b+1, b+n+1);

	for (int i = 1; i <= n; i++)
		dp[i] = inf;

	for (int i = 2; i <= n; i++)
	{
		if (a[i] != b[i])
			dp[i] = min(dp[i], 1ll*abs(a[i]-b[i]) + dp[i-1]);

		dp[i] = min(dp[i], dp[i-2] + cost(i-1, i));

		if (i >= 3)
			dp[i] = min(dp[i], dp[i-3] + cost(i-2, i));
	}

	printf("%lld\n", dp[n]);
}
