// Codeforces 1453E - Dog Snacks
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int n;
int nivel[maxn], dp[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		dfs(v, u);
	}
}

void solve(int u, int p, int k)
{
	int mx = 0, mn = inf;
	int qtd_igual = 0;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		solve(v, u, k);

		mx = max(mx, dp[v]);
		mn = min(mn, dp[v]);

		if (dp[v] == k) qtd_igual++;
	}

	if (grafo[u].size() == 1 && u != 1) dp[u] = nivel[u];
	else if (u != 1)
	{
		if (mx-nivel[u]+1 > k) dp[u] = inf;
		else dp[u] = mn;
	}
	else
	{
		if (mx > k || qtd_igual > 1) dp[u] = inf;
		else dp[u] = mn;
	}
}

bool ok(int k)
{
	for (int i = 1; i <= n; i++)
		dp[i] = inf;

	solve(1, 0, k);

	return dp[1] <= k;
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			grafo[i].clear(), nivel[i] = 0;

		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}

		dfs(1, 0);

		int ini = 1, fim = n, ans = n;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (ok(mid)) ans = mid, fim = mid-1;
			else ini = mid+1;
		}

		printf("%d\n", ans);
	}
}
