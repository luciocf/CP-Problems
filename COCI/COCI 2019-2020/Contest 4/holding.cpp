// COCI 2019/2020 - Holding
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;
const int maxk = 2505;
const int inf = 1e9+10;

int a[maxn];
int dp1[maxn][maxn][maxk], dp2[maxn][maxn][maxk];

int main(void)
{
	int n, l, r, k;
	scanf("%d %d %d %d", &n, &l, &r, &k);
	k = min(k, maxk-1);

	int soma = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		if (i >= l && i <= r)
			soma += a[i];
	}

	for (int i = 1; i < l; i++)
	{
		for (int j = l; j <= r; j++)
		{
			for (int x = 0; x <= k; x++)
			{
				dp1[i][j][x] = max(dp1[i][j-1][x], dp1[i-1][j][x]);

				if (x >= j-i)
					dp1[i][j][x] = max(dp1[i][j][x], a[j] - a[i] + dp1[i-1][j-1][x-(j-i)]);
			}
		}
	}

	for (int i = r; i >= l; i--)
	{
		for (int j = n; j > r; j--)
		{
			for (int x = 0; x <= k; x++)
			{
				dp2[i][j][x] = max(dp2[i+1][j][x], dp2[i][j+1][x]);

				if (x >= j-i)
					dp2[i][j][x] = max(dp2[i][j][x], a[i] - a[j] + dp2[i+1][j+1][x-(j-i)]);
			}
		}
	}

	int ans = 0;

	for (int x = 0; x <= k; x++)
		ans = max(ans, dp1[l-1][r][x]);
	for (int x = 0; x <= k; x++)
		ans = max(ans, dp2[l][r+1][x]);

	for (int i = l; i <= r; i++)
		for (int x = 0; x <= k; x++)
			ans = max(ans, dp1[l-1][i][x] + dp2[i+1][r+1][k-x]);

	printf("%d\n", soma-ans);
}
