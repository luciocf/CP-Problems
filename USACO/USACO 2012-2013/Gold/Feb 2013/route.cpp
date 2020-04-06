// USACO 2012/2013 - Route Design
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn], b[maxn];

int dp[maxn];

vector<int> grafo[maxn];

int main(void)
{
	freopen("route.in", "r", stdin); freopen("route.out", "w", stdout);

	int n, m, r;
	scanf("%d %d %d", &n, &m, &r);

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		ans = max(ans, a[i]);
	}

	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &b[i]);
		ans = max(ans, b[i]);
	}

	for (int i = 1; i <= r; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		dp[i] = a[i];

	for (int i = 1; i <= m; i++)
	{
		sort(grafo[i].begin(), grafo[i].end());

		int mx = b[i];

		for (auto j: grafo[i])
		{
			int aux = dp[j];

			dp[j] = max(dp[j], a[j] + mx);

			mx = max(mx, aux+b[i]);
			ans = max({ans, dp[j], aux+b[i]});
		}
	}

	printf("%d\n", ans);
}
