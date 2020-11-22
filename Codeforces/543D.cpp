// Codeforces 543D - Road Improvement
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int mod = 1e9+7;

int ans[maxn];
int dp[maxn];

int fora[maxn];
vector<int> grafo[maxn], pref[maxn], suf[maxn];

void dfs(int u, int p)
{
	dp[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		dp[u] = (1ll*dp[u]*(1+dp[v]))%mod;
	}
}

void solve(int u, int p)
{
	ans[u] = dp[u];

	for (int i = 0; i < grafo[u].size(); i++)
	{
		int v = grafo[u][i];
		if (v == p) continue;

		fora[v] = 1ll*(i == 0 ? 1 : pref[u][i-1])*(i == grafo[u].size()-1 ? 1 : suf[u][i+1])%mod;
		fora[v] = (1ll*fora[v]*fora[u])%mod;
		fora[v] = (fora[v]+1)%mod;

		dp[v] = (1ll*dp[v]*fora[v])%mod;

		pref[v].resize(grafo[v].size()); suf[v].resize(grafo[v].size());

		for (int j = 0; j < grafo[v].size(); j++)
		{
			int w = grafo[v][j];

			if (w == u)
			{
				if (j == 0) pref[v][j] = 1;
				else pref[v][j] = pref[v][j-1];

				continue;
			}

			pref[v][j] = 1ll*(j == 0 ? 1 : pref[v][j-1])*(1+dp[w])%mod;
		}

		for (int j = grafo[v].size()-1; j >= 0; j--)
		{
			int w = grafo[v][j];

			if (w == u)
			{
				if (j == grafo[v].size()-1) suf[v][j] = 1;
				else suf[v][j] = suf[v][j+1];
				
				continue;
			}

			suf[v][j] = 1ll*(j == grafo[v].size()-1 ? 1 : suf[v][j+1])*(1+dp[w])%mod;
		}

		solve(v, u);
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		grafo[i].push_back(p);
		grafo[p].push_back(i);
	}

	dfs(1, 0);

	fora[1] = 1;
	pref[1].resize(grafo[1].size()); suf[1].resize(grafo[1].size());

	for (int i = 0; i < grafo[1].size(); i++)
	{
		int v = grafo[1][i];

		pref[1][i] = 1ll*(i == 0 ? 1 : pref[1][i-1])*(1+dp[v])%mod;
	}

	for (int i = grafo[1].size()-1; i >= 0; i--)
	{
		int v = grafo[1][i];

		suf[1][i] = 1ll*(i == grafo[1].size()-1 ? 1 : suf[1][i+1])*(1+dp[v])%mod;
	}

	solve(1, 0);

	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);

	printf("\n");
}
