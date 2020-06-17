// Codeforces 1168C - And Reachability
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

int n;
int a[maxn];

int last[21];
int dp[maxn][21];

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = n; i >= 1; i--)
	{
		for (int j = 0; j <= 20; j++)
			dp[i][j] = n+1;

		for (int j = 0; j <= 20; j++)
		{
			if (!last[j] || !(a[i]&(1<<j))) continue;

			int u = last[j];

			for (int b = 0; b <= 20; b++)
				dp[i][b] = min(dp[i][b], dp[u][b]);
		}

		for (int j = 0; j <= 20; j++)
		{
			if (a[i]&(1<<j))
			{
				dp[i][j] = i;
				last[j] = i;
			}
		}
	}

	while (q--)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		bool ok = false;
		for (int i = 0; i <= 20; i++)
			if (a[v]&(1<<i))
				ok |= (dp[u][i] <= v);

		if (ok) printf("Shi\n");
		else printf("Fou\n");
	}
}
