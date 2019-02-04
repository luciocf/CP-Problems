// Seletiva IOI 2017 - Tribo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

const int maxk = 55;

const int inf = 1e9+10;

typedef pair<int, int> pii;

int dp[maxn][maxk], aux[maxn][maxk], k;

vector<pii> grafo[maxn];

void solve(int u, int p)
{
	for (int i = 2; i <= k; i++)
		dp[u][i] = inf;

	for (auto pp: grafo[u])
	{
		int v = pp.first, d = pp.second;
		if (v == p) continue;

		solve(v, u);

		for (int i = 2; i <= k; i++)
			aux[u][i] = inf;

		for (int i = 2; i <= k; i++)
			for (int j = 1; j < i; j++)
				aux[u][i] = min(aux[u][i], d+dp[v][j]+dp[u][i-j]);

		for (int i = 2; i <= k; i++)
			dp[u][i] = min(dp[u][i], aux[u][i]);
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);
	
	int n;
	cin >> n >> k;

	for (int i = 1; i <= n-1; i++)
	{
		int u, v, d;
		cin >> u >> v >> d;

		grafo[u].push_back({v, d});
		grafo[v].push_back({u, d});
	}

	solve(1, 0);

	int ans = inf;
	for (int i = 1; i <= n; i++)
		ans = min(ans, dp[i][k]);

	cout << ans << "\n";
}