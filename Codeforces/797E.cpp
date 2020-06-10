// Codeforces 797E - Array Queries
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int bucket = 320;

int n;
int a[maxn];

int dp[maxn][bucket];

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j < bucket; j++)
		{
			if (i+a[i]+j > n) dp[i][j] = 1;
			else dp[i][j] = 1 + dp[i+a[i]+j][j];
		}
	}

	int q;
	scanf("%d", &q);
	
	while (q--)
	{
		int p, k;
		scanf("%d %d", &p, &k);

		if (k < bucket) printf("%d\n", dp[p][k]);
		else
		{	
			int ans = 0;

			while (p <= n)
			{
				++ans;
				p += a[p]+k;
			}

			printf("%d\n", ans);
		}
	}
}
