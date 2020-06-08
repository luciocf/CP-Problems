// USACO 2014/2015 Gold - Cow Hopscotch
// Lúcio Cardoso 

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 755;
const int mod = 1e9+7;

int a[maxn][maxn];

int id_cor[maxn*maxn];

int soma[maxn][maxn];
int dp[maxn][maxn];

vector<pii> pos[maxn*maxn];

int bit[maxn][2000];

void upd(int x, int v, int k)
{
	for (; x < maxn; x += (x&-x))
		bit[x][k] = (bit[x][k] + v)%mod;
}

int get(int x, int k)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans = (ans + bit[x][k])%mod;
	return ans;
}

int main(void)
{
	freopen("hopscotch.in", "r", stdin); freopen("hopscotch.out", "w", stdout);

	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);

			pos[a[i][j]].push_back({i, j});
		}
	}

	int ind_aux = 0;

	for (int i = 1; i <= k; i++)
		if (pos[i].size() > 500)
			id_cor[i] = ++ind_aux;
		
	dp[1][1] = 1;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int c = a[i][j];

			dp[i][j] += soma[i-1][j-1];

			if (pos[c].size() <= 500)
			{
				for (auto pp: pos[c])
					if (pp.first < i && pp.second < j)
						dp[i][j] = (dp[i][j] - dp[pp.first][pp.second] + mod)%mod;
			}
			else
			{
				c = id_cor[c];

				dp[i][j] = (dp[i][j] - get(j-1, c) + mod)%mod;
			}

			soma[i][j] = (((soma[i-1][j] + soma[i][j-1])%mod - soma[i-1][j-1] + mod)%mod + dp[i][j])%mod;
		}

		for (int j = 1; j <= m; j++)
		{
			int c = a[i][j];

			if (pos[c].size() > 500)
			{
				c = id_cor[c];

				upd(j, dp[i][j], c);
			}
		}
	}

	printf("%d\n", dp[n][m]);
}
