// APIO 2009 - Digging for Oil
// Lúcio Cardoso

// Solution is the same as in: https://github.com/timpostuvan/competitive-programming/blob/master/Olympiad/APIO/Oil2009.cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1510;
const ll inf = 1e18+10;

int n, m, k;
int a[maxn][maxn];

ll S[maxn][maxn];

ll pref[2][maxn], suf[2][maxn];
ll pref2[2][maxn], suf2[2][maxn];

ll mx[4][maxn][maxn];

ll soma(int i, int j)
{
	if (i-k+1 < 1 || j-k+1 < 1) return -inf;
	if (i < 1 || i > n || j < 1 || j > m) return -inf;

	return (S[i][j]-S[i-k][j]-S[i][j-k]+S[i-k][j-k]);
}

void calc1(void)
{
	for (int i = 0; i < maxn; i++)
		pref[0][i] = pref[1][i] = suf[0][i] = suf[1][i] = -inf;

	for (int i = 1; i <= n; i++)
	{
		pref[0][i] = pref[0][i-1];

		for (int j = 1; j <= m; j++)
			pref[0][i] = max(pref[0][i], soma(i, j));
	}

	for (int j = 1; j <= m; j++)
	{
		pref[1][j] = pref[1][j-1];

		for (int i = 1; i <= n; i++)
			pref[1][j] = max(pref[1][j], soma(i, j));
	}

	for (int i = n; i >= 1; i--)
	{
		suf[0][i] = suf[0][i+1];

		for (int j = 1; j <= m; j++)
			suf[0][i] = max(suf[0][i], soma(i+k-1, j));
	}

	for (int j = m; j >= 1; j--)
	{
		suf[1][j] = suf[1][j+1];

		for (int i = 1; i <= n; i++)
			suf[1][j] = max(suf[1][j], soma(i, j+k-1));
	}
}

void calcmx(void)
{
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			mx[0][i][j] = mx[1][i][j] = mx[2][i][j] = mx[3][i][j] = -inf;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			mx[0][i][j] = max({mx[0][i-1][j], mx[0][i][j-1], soma(i, j)});

	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--)
			mx[1][i][j] = max({mx[1][i-1][j], mx[1][i][j+1], soma(i, j+k-1)});

	for (int i = n; i >= 1; i--)
		for (int j = m; j >= 1; j--)
			mx[2][i][j] = max({mx[2][i+1][j], mx[2][i][j+1], soma(i+k-1, j+k-1)});

	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= m; j++)
			mx[3][i][j] = max({mx[3][i+1][j], mx[3][i][j-1], soma(i+k-1, j)});
}

void calc2(void)
{
	for (int i = 0; i < maxn; i++)
		pref2[0][i] = pref2[1][i] = suf2[0][i] = suf2[1][i] = -inf;

	for (int i = 1; i <= n; i++)
	{
		pref2[0][i] = pref2[0][i-1];

		for (int j = 1; j <= m; j++)
		{
			if (i-k >= 1 && pref[0][i-k] != -inf)
				pref2[0][i] = max(pref2[0][i], soma(i, j) + pref[0][i-k]);

			if (j-k >= 1 && mx[0][i][j-k] != -inf)
				pref2[0][i] = max(pref2[0][i], soma(i, j) + mx[0][i][j-k]);

			if (j+1 <= m && mx[1][i][j+1] != -inf)
				pref2[0][i] = max(pref2[0][i], soma(i, j) + mx[1][i][j+1]);
		}
	}

	for (int j = 1; j <= m; j++)
	{
		pref2[1][j] = pref2[1][j-1];

		for (int i = 1; i <= n; i++)
		{
			if (i-k >= 1 && mx[0][i-k][j] != -inf)
				pref2[1][j] = max(pref2[1][j], soma(i, j) + mx[0][i-k][j]);

			if (i+1 <= n && mx[3][i+1][j] != -inf)
				pref2[1][j] = max(pref2[1][j], soma(i, j) + mx[3][i+1][j]);

			if (j-k >= 1 && pref[1][j-k] != -inf)
				pref2[1][j] = max(pref2[1][j], soma(i, j) + pref[1][j-k]);
		}
	}

	for (int i = n; i >= 1; i--)
	{
		suf2[0][i] = suf2[0][i+1];

		for (int j = 1; j <= m; j++)
		{
			if (i+k <= n && suf[0][i+k] != -inf)
				suf2[0][i] = max(suf2[0][i], soma(i+k-1, j) + suf[0][i+k]);

			if (j+1 <= m && mx[2][i][j+1] != -inf)
				suf2[0][i] = max(suf2[0][i], soma(i+k-1, j) + mx[2][i][j+1]);

			if (j-k >= 1 && mx[3][i][j-k] != -inf)
				suf2[0][i] = max(suf2[0][i], soma(i+k-1, j) + mx[3][i][j-k]);
		}
	}

	for (int j = m; j >= 1; j--)
	{
		suf2[1][j] = suf2[1][j+1];

		for (int i = 1; i <= n; i++)
		{
			if (i+1 <= n && mx[2][i+1][j] != -inf)
				suf2[1][j] = max(suf2[1][j], soma(i, j+k-1) + mx[2][i+1][j]);

			if (i-k >= 1 && mx[1][i-k][j] != -inf)
				suf2[1][j] = max(suf2[1][j], soma(i, j+k-1) + mx[1][i-k][j]);

			if (j+k <= m && suf[1][j+k] != -inf)
				suf2[1][j] = max(suf2[1][j], soma(i, j+k-1) + suf[1][j+k]);
		}
	}
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			S[i][j] = 1ll*a[i][j] + S[i-1][j] + S[i][j-1] - S[i-1][j-1];

	calc1(); calcmx(); calc2();


	ll ans = 0;

	for (int i = 0; i <= n; i++)
		ans = max({ans, pref[0][i] + suf2[0][i+1], pref2[0][i] + suf[0][i+1]});

	for (int j = 1; j <= m; j++)
		ans = max({ans, pref[1][j] + suf2[1][j+1], pref2[1][j] + suf[1][j+1]});

	printf("%lld\n", ans);
}
