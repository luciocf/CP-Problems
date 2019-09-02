// CEOI 2017 Practice Session - Museum
// Lúcio Cardoso

// Solution: https://ceoi2017.acm.si/files/ceoi2017-solutions-practice.pdf

#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e4+10;
const int inf = 1e8+10;
 
int n, k, x;
int sz[maxn];
 
int dp[maxn][maxn][2];
 
vector<pii> grafo[maxn];
 
void dfs(int u, int p)
{
	sz[u] = 1;
 
	for (auto pp: grafo[u])
	{
		int v = pp.first;
		if (v == p) continue;
 
		dfs(v, u);
		sz[u] += sz[v];
	}
}
 
void solve(int u, int p)
{
	for (int i = 2; i <= k; i++)
		dp[u][i][0] = dp[u][i][1] = inf;
 
	int soma_sz = 1;
 
	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p) continue;
 
		solve(v, u);
 
		soma_sz += sz[v];
 
		for (int i = soma_sz; i >= 2; i--)
		{
			for (int j = max(0, i-soma_sz+sz[v]); j <= min(i, sz[v]); j++)
			{
				int c1 = dp[u][i-j][0] + 2*w + dp[v][j][1];
				int c2 = dp[u][i-j][1] + w + dp[v][j][0];
 
				dp[u][i][0] = min({dp[u][i][0], c1, c2});
 
				dp[u][i][1] = min(dp[u][i][1], dp[u][i-j][1] + 2*w + dp[v][j][1]);
			}
		}
	}
}
 
int main(void)
{
	scanf("%d %d %d", &n, &k, &x);
 
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
 
		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}
 
	dfs(x, 0);
	solve(x, 0);
 
	printf("%d\n", dp[x][k][0]);
 
}
