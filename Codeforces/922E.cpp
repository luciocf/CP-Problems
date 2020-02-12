// Codeforces 922E - Birds
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e4+10;
const ll inf = 1e18;

ll dp[maxn];

int c[maxn];
int cost[maxn];

int main(void)
{
	int n, W, B, X;
	scanf("%d %d %d %d", &n, &W, &B, &X);

	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &cost[i]);

	for (int i = 1; i < maxn; i++)
		dp[i] = -inf;

	dp[0] = W;

	for (int i = 1; i <= n; i++)
		for (int j = 10000; j >= 0; j--)
			for (int k = c[i]; k >= 0; k--)
				if (dp[j] - 1ll*k*cost[i] >= 0)
					dp[j+k] = max(dp[j+k], min(1ll*B*(j+k) + 1ll*W, 1ll*X + dp[j] - 1ll*cost[i]*k));

	for (int i = 10000; i >= 0; i--)
	{
		if (dp[i] >= 0)
		{
			printf("%d\n", i);
			return 0;
		}
	}
}
