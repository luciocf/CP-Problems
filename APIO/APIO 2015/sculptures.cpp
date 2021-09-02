// APIO 2015 - Bali Sculptures
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e3+10;
const int inf = 1e9;

int n;
int a[maxn];

ll pref[maxn];

int dp[maxn][maxn];

bool bad(ll s, ll mask, int pos)
{
	ll x = ((1ll<<61)-1) ^ ((1ll<<(pos))-1);
	s &= x;

	return (mask & (mask ^ s)) != (mask ^ s);
}

int main(void)
{
	int A, B;
	scanf("%d %d %d", &n, &A, &B);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pref[i] = pref[i-1] + 1ll*a[i]; 
	}

	if (A != 1)
	{
		ll mask = 0;

		for (int b = 60; b >= 0; b--)
		{
			dp[0][0] = 1;

			for (int i = 0; i <= n; i++)
				for (int j = 1; j <= n; j++)
					dp[i][j] = 0;

			for (int k = 1; k <= n; k++)
			{
				for (int i = 1; i <= n; i++)
				{
					for (int j = i; j >= 1; j--)
					{
						ll s = pref[i] - pref[j-1];

						if (dp[k-1][j-1] && !bad(s, mask, b))
							dp[k][i] = 1;
					}
				}
			}


			bool ok = 0;
			for (int i = A; i <= B; i++)
				if (dp[i][n])
					ok = 1;

			if (!ok) mask += (1ll<<b);
		}

		printf("%lld\n", mask);

		return 0;
	}


	ll mask = 0;

	for (int b = 60; b >= 0; b--)
	{
		for (int i = 1; i <= n; i++)
			dp[0][i] = inf;

		for (int i = 1; i <= n; i++)
		{
			for (int j = i; j >= 1; j--)
			{
				ll s = pref[i] - pref[j-1];

				if (dp[0][j-1] != inf && !bad(s, mask, b))
					dp[0][i] = min(dp[0][i], dp[0][j-1] + 1);
			}
		}

		if (dp[0][n] > B) mask += (1ll<<b);
	}

	printf("%lld\n", mask);
}
