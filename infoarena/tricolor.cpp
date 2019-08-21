// infoarena - Tricolor
// Lúcio Cardoso

// Solution:

// 1. Use two DPs:
//	* dp1[u] -> greatest amount of twin nodes using only vertices in the subtree of u, if u is white.
// 	* dp2[u][k] -> greatest amount of twin nodes using only vertices in the subtree of u, if u is black
//  and there are k white nodes reachable from u by using only black vertices (or no vertex).

// 2. The following DPs can be calculated in O(n^3). However, by visiting only possible states,
// we can significantly speed up the solution. 

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e3+10;
 
int n;
 
int sz[maxn];
 
int dp1[maxn];
int dp2[maxn][maxn];
 
bool ok[maxn][maxn];
 
bool mark[maxn][2];
 
vector<int> grafo[maxn];
 
void dfs(int u, int p)
{
	sz[u] = 1;
 
	for (auto v: grafo[u])
	{
		if (v == p) continue;
 
		dfs(v, u);
 
		sz[u] += sz[v];
	}
}
 
void solve(int u, int p, int cor)
{
	if (mark[u][cor]) return;
	mark[u][cor] = 1;
 
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			solve(v, u, 0);
			solve(v, u, 1);
		}
	}
 
	if (cor == 0)
	{
		for (auto v: grafo[u])
		{
			if (v == p) continue;
 
			int ans = 1+dp1[v];
 
			for (int k = 1; k <= sz[v]; k++)
			{
				if (!ok[v][k]) break;
 
				ans = max(ans, dp2[v][k]+k);
			}
 
			dp1[u] += ans;
		}
	}
	else
	{
		int tot = 0;
 
		for (auto v: grafo[u])
		{
			if (v == p) continue;
 
			tot += sz[v];
 
			for (int k = tot; k >= 1; k--)
			{
				int ans = 0;
 
				if (tot == sz[v])
				{
					if (k == 1)
					{
						dp2[u][k] = dp1[v];
						ok[u][1] = 1;
					}
 
					if (ok[v][k])
					{
						ok[u][k] = 1;
						dp2[u][k] = max(dp2[u][k], dp2[v][k]);
					}
 
					continue;
				}
 
				for (int j = min(k, sz[v]); j >= 1; j--)
				{
					if (!ok[u][k-j]) break;
 
					if (j == 1 && ok[u][k-1])
					{
						ans = max(ans, dp1[v] + dp2[u][k-1] + k-1);
						ok[u][k] = 1;
					}
 
					if (ok[v][j] && ok[u][k-j])
					{
						ans = max(ans, dp2[v][j] + dp2[u][k-j] + (k-j)*j);
						ok[u][k] = 1;
					}
				}
 
				dp2[u][k] = max(dp2[u][k], ans);
			}
		}
	}
}
 
int main(void)
{
	freopen("tricolor.in", "r", stdin);
	freopen("tricolor.out", "w", stdout);
 
	int T;
	scanf("%d", &T);
 
	while (T--)
	{
		scanf("%d", &n);
 
		memset(dp1, 0, sizeof dp1); memset(dp2, 0, sizeof dp2);
		memset(ok, 0, sizeof ok); memset(mark, 0, sizeof mark);
 
		for (int i = 1; i <= n; i++)
		{
			grafo[i].clear();
			ok[i][0] = 1;
		}
 
		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);
 
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
 
		dfs(1, 0);
		solve(1, 0, 0); solve(1, 0, 1);
 
		int ans = dp1[1];
		for (int i = 0; i <= n; i++)
			ans = max(ans, dp2[1][i]);
 
		printf("%d\n", ans);
	}
}
