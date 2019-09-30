// POI 2016 - Messenger
// Lúcio Cardoso

// 1. Let ways[i][j][k] be the amount of paths starting at i and ending at j that pass
// through k edges. We can calculate this in O(n * m * D).

// 2. Fix a pair of vertices (u, v). Let good[a][b][k] (where a and b belong to {u, v}) be the
// amount of paths starting at a and ending at b, visiting k edges such that neither u nor v
// are visited as intermediate vertices (they can be endpoints). Now, to calculate good[a][b][k],
// use the recurrence the end of the official solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2016/editorial/pos.pdf

// Note: In this code, good[a][b][k] is "ans[a][b][k]". Also, ways[i][j][k] is "dp[i][j][k]".

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 110;
const int maxk = 55;

ll dp[maxn][maxn][maxk];
ll ans[maxn][maxn][maxk];
int tot[maxn][maxn][maxk];

vector<int> grafo[maxn];

int main(void)
{
	int n, m, mod;
	scanf("%d %d %d", &n, &m, &mod);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		dp[u][v][1] = 1;
	}

	for (int i = 1; i <= n; i++)
		dp[i][i][0] = 1;

	for (int k = 2; k < maxk; k++)
		for (int u = 1; u <= n; u++)
			for (int v = 1; v <= n; v++)
				for (auto w: grafo[u])
					dp[u][v][k] = (dp[u][v][k] + dp[w][v][k-1])%mod;

	for (int u = 1; u <= n; u++)
	{
		for (int v = 1; v <= n; v++)
		{
			for (int k = 1; k < maxk; k++)
			{
				ans[u][v][k] = dp[u][v][k];
				ans[u][u][k] = dp[u][u][k];
				ans[v][u][k] = dp[v][u][k];
				ans[v][v][k] = dp[v][v][k];

				for (int x = 1; x < k; x++)
				{
					ans[u][v][k] -= (dp[u][u][x] * ans[u][v][k-x])%mod;
					ans[u][v][k] = (ans[u][v][k] + mod)%mod;

					ans[u][v][k] -= (dp[u][v][x] * ans[v][v][k-x])%mod;
					ans[u][v][k] = (ans[u][v][k] + mod)%mod;

					ans[u][u][k] -= (dp[u][u][x] * ans[u][u][k-x])%mod;
					ans[u][u][k] = (ans[u][u][k] + mod)%mod;

					ans[u][u][k] -= (dp[u][v][x] * ans[v][u][k-x])%mod;
					ans[u][u][k] = (ans[u][u][k] + mod)%mod;

					ans[v][u][k] -= (dp[v][u][x] * ans[u][u][k-x])%mod;
					ans[v][u][k] = (ans[v][u][k] + mod)%mod;

					ans[v][u][k] -= (dp[v][v][x] * ans[v][u][k-x])%mod;
					ans[v][u][k] = (ans[v][u][k] + mod)%mod;

					ans[v][v][k] -= (dp[v][u][x] * ans[u][v][k-x])%mod;
					ans[v][v][k] = (ans[v][v][k] + mod)%mod;

					ans[v][v][k] -= (dp[v][v][x] * ans[v][v][k-x])%mod;
					ans[v][v][k] = (ans[v][v][k] + mod)%mod;
				}

				tot[u][v][k] = ans[u][v][k];
			}
		}
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int u, v, k;
		scanf("%d %d %d", &u, &v, &k);

		printf("%d\n", tot[u][v][k]);
	}
}
