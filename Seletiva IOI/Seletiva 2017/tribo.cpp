// Seletiva IOI 2017 - Tribo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e4+10;
const int maxk = 55;
const int inf = 1e9+10;

int n, k;

int dp[maxn][maxk];

vector<pii> grafo[maxn];

void solve(int u, int p)
{
	for (int i = 2; i <= k; i++)
		dp[u][i] = inf;

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p) continue;

		solve(v, u);

		for (int i = k; i >= 2; i--)
			for (int j = 1; j < i; j++)
				dp[u][i] = min(dp[u][i], dp[v][j]+w+dp[u][i-j]);
	}
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	solve(1, 0);

	int ans = inf;
	for (int i = 1; i <= n; i++)
		ans = min(ans, dp[i][k]);

	printf("%d\n", ans);
}
