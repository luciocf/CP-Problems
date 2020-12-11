// Codeforces 425B - Sereja and Table
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;
const int inf = 1e9+10;

int n, m, k;
int a[maxn][maxn];

int getans(vector<int> &mask, int q)
{
	int ans = 0;

	if (q)
	{
		for (int i = 1; i <= n; i++)
		{
			int v1 = 0, v2 = 0;

			for (int j = 1; j <= m; j++)
			{
				if (mask[j-1] != a[i][j]) v1++;
				else v2++;
			}

			ans += min(v1, v2);
		}

		return ans;
	}

	for (int i = 1; i <= m; i++)
	{
		int v1 = 0, v2 = 0;

		for (int j = 1; j <= n; j++)
		{
			if (mask[j-1] != a[j][i]) v1++;
			else v2++;
		}

		ans += min(v1, v2);
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);

	int ans = inf;

	if (n <= k)
	{
		vector<int> msk(n);

		for (int mask = 0; mask < (1<<n); mask++)
		{
			for (int i = 0; i < n; i++)
				msk[i] = (mask&(1<<i) ? 1 : 0);

			if (getans(msk, 0) <= k) ans = min(ans, getans(msk, 0));
		}
	}
	else
	{
		vector<int> mask(m);

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				mask[j-1] = a[i][j];

			if (getans(mask, 1) <= k) ans = min(ans, getans(mask, 1));
		}
	}

	if (ans == inf) printf("-1\n");

	else printf("%d\n", ans);
}
