// infoarena - Arbore7
// Lúcio Cardoso

// Solution:

// 1. Let dp[u][0] be the greatest amount of connected components that it's possible to achieve
// considering only the subtree of u and removing node u. Also, dp[u][1] has the same meaning, except
// we keep u.

// dp[u][0] += max(dp[v][0], dp[v][1]+1)
// dp[u][1] += max(dp[v][0], dp[v][1]), for every child v of u.

// 2. We can keep a similar dp that calculates the amount of ways for each
// of dp[u][0] and dp[u][1]. Check the code for further details.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e9+7;

int n;

int dp[maxn][2];
int dp2[maxn][2];

vector<int> grafo[maxn];

void solve(int u, int p)
{
	dp2[u][0] = dp2[u][1] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		solve(v, u);

		// m is the value that dp[u][0] will assume
		int m = dp[u][0]+max(1+dp[v][1], dp[v][0]);
		int tot = 0;

		// increase the amount of ways checking which dp from v is greater
		if (dp[u][0]+dp[v][1]+1 == m) tot += (1ll*dp2[u][0]*dp2[v][1])%mod;
		if (dp[u][0]+dp[v][0] == m) tot += (1ll*dp2[u][0]*dp2[v][0])%mod;

		dp[u][0] = m;
		dp2[u][0] = tot%mod;

		// now do the same for dp[u][1]
		
		m = dp[u][1]+max(dp[v][1], dp[v][0]);
		tot = 0;

		if (dp[u][1]+dp[v][1] == m) tot += (1ll*dp2[u][1]*dp2[v][1])%mod;
		if (dp[u][1]+dp[v][0] == m) tot += (1ll*dp2[u][1]*dp2[v][0])%mod;

		dp[u][1] = m;
		dp2[u][1] = tot%mod;
	}
}

int main(void)
{
	freopen("arbore7.in", "r", stdin);
	freopen("arbore7.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	solve(1, 0);

	int m = max(1+dp[1][1], dp[1][0]);
	int tot = 0;

	if (dp[1][1]+1 == m)
		tot += dp2[1][1];
	if (dp[1][0] == m)
		tot += dp2[1][0];

	printf("%d %d\n", m, tot);
}
