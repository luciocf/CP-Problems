// Codeforces 1372E - Omkar and Last Floor
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 110;

int n, m;

pii range[maxn][maxn];

ll dp[maxn][maxn];

ll solve(int l, int r)
{
	if (l > r) return 0;
	if (dp[l][r] != -1) return dp[l][r];

	ll ans = 0;

	for (int i = l; i <= r; i++)
	{
		ll qtd = 0;

		for (int j = 1; j <= n; j++)
			if (range[j][i].ff >= l && range[j][i].ss <= r)
				++qtd;

		ans = max(ans, 1ll*qtd*qtd + solve(l, i-1) + solve(i+1, r));
	}

	return dp[l][r] = ans;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);

		while (k--)
		{
			int l, r;
			scanf("%d %d", &l, &r);

			for (int j = l; j <= r; j++)
				range[i][j] = {l, r};
		}
	}

	memset(dp, -1, sizeof dp);
	printf("%lld\n", solve(1, m));
}
