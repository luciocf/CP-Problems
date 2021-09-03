// BOI 2021 - The Xana Coup
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int a[maxn];

ll dp[maxn][2][2];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			dp[u][i][j] = inf;

	if (grafo[u].size() == 1 && u != 1)
	{
		if (a[u] == 0)
		{
			dp[u][0][0] = 0;
			dp[u][1][1] = 1;
		}
		else
		{
			dp[u][1][0] = 0;
			dp[u][0][1] = 1;
		}

		return;
	}

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	vector<ll> ord;
	int par;
	ll ans;

	// dp[u][0/1][0] -> n vou ativar

	for (int k = 0; k < 2; k++)
	{
		par = (a[u] != k), ans = 0;
		ord.clear();

		for (auto v: grafo[u])
		{
			if (v == p) continue;

			ans += dp[v][0][0];
			ord.push_back(dp[v][0][1] - dp[v][0][0]);
		}

		sort(ord.begin(), ord.end());

		if (!par) dp[u][k][0] = min(dp[u][k][0], ans);

		for (int i = 0; i < ord.size(); i++)
		{
			ans += ord[i];

			if ((i+1)%2 == par)
				dp[u][k][0] = min(dp[u][k][0], ans);
		}
	}

	// dp[u][0/1][1] -> vou ativar

	for (int k = 0; k < 2; k++)
	{
		par = ((a[u]^1) != k), ans = 0;
		ord.clear();

		for (auto v: grafo[u])
		{
			if (v == p) continue;

			ans += dp[v][1][0];
			ord.push_back(dp[v][1][1] - dp[v][1][0]);
		}

		sort(ord.begin(), ord.end());

		if (!par) dp[u][k][1] = min(dp[u][k][1], ans + 1);

		for (int i = 0; i < ord.size(); i++)
		{
			ans += ord[i];

			if ((i+1)%2 == par)
				dp[u][k][1] = min(dp[u][k][1], ans + 1);
		}
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	dfs(1, 0);

	ll ans = min(dp[1][0][0], dp[1][0][1]);

	if (ans == inf) printf("impossible\n");
	else printf("%lld\n", ans);
}
