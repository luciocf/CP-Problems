// BOI 2019 - Kitchen
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 310;
const int maxs = 9e4+10;
const int inf = 1e9+10;

int n, m, k, tot;

int a[maxn], b[maxn];

int dp[maxs];

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		tot += a[i];
	}

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	for (int i = 1; i <= n; i++)
	{
		if (a[i] < k)
		{
			printf("Impossible\n");
			return 0;
		}
	}

	for (int i = 1; i < maxs; i++)
		dp[i] = -inf;

	for (int i = 1; i <= m; i++)
		for (int j = maxs-1; j >= b[i]; j--)
			dp[j] = max(dp[j], dp[j-b[i]]+min(b[i], n));

	int ans = -1;
	for (int i = tot; i < maxs; i++)
	{
		if (dp[i] >= n*k)
		{
			ans = i;
			break;
		}
	}

	if (ans == -1) printf("Impossible\n");
	else printf("%d\n", ans-tot);
}
