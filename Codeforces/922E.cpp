// Codeforces 922E - Birds
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e4+10;

ll dp[1010][maxn];

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

	memset(dp, -1, sizeof dp);

	dp[1][0] = W;

	for (int i = 1; i <= n; i++)
		for (int j = 10000; j >= 0; j--)
			for (int k = 0; k <= c[i]; k++)
				if (dp[i][j] - 1ll*k*cost[i] >= 0)
					dp[i+1][j+k] = max(dp[i+1][j+k], min(1ll*B*(j+k) + 1ll*W, 1ll*X + dp[i][j] - 1ll*cost[i]*k));

	for (int i = 10000; i >= 0; i--)
	{
		if (dp[n+1][i] >= 0)
		{
			printf("%d\n", i);
			return 0;
		}
	}
}
