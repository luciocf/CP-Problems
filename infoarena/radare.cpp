// infoarena - Radare
// Lúcio Cardoso

// Solution: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/radare.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3010;
const int mod = 31333;

int n, p;
int a[maxn];

int pot[maxn];

int st[maxn], en[maxn], back[maxn], tt;
int sz[maxn];

int dp[maxn][maxn+500];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt, sz[u] = 1;
	back[tt] = u;

	for (auto v: grafo[u])
	{
		if (v != p)
		{
			dfs(v, u);
			sz[u] += sz[v];
		}
	}

	en[u] = tt;
}

int main(void)
{
	freopen("radare.in", "r", stdin); freopen("radare.out", "w", stdout);

	scanf("%d %d", &n, &p);

	pot[0] = 1;
	for (int i = 1; i <= n; i++)
		pot[i] = (2*pot[i-1])%mod;

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

	dp[n+1][0] = 1;

	for (int i = n; i >= 2; i--)
	{
		int u = back[i];

		for (int j = 0; j <= p; j++)
		{
			if (j >= a[u]) dp[i][j] = dp[i+1][j-a[u]];

			dp[i][j] = (dp[i][j] + (1ll*pot[sz[u]-1]*dp[en[u]+1][j])%mod)%mod;
		}
	}

	printf("%d\n", dp[2][p-a[1]]);
}
