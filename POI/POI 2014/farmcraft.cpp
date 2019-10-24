// POI 2014 - FarmCraft
// Lúcio Cardoso

// Solution:

// 1. Let dp[u] be the answer for the subtree of u. Use exchange arguments to prove that
// it's optimal to sort the children of u by the value (dp[v] - 2*sz[v]), where sz[v] is the
// size of the subtree rooted at v.

// 2. Now, we can easily calculate the dp for u, since dp[u] = max(dp[v] + 2*S(v)+1), where
// S(v) is the sum of the children of u that come before v.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int n;
int tt[maxn];

int sz[maxn];

int dp[maxn];

vector<int> grafo[maxn];

bool comp(int a, int b)
{
	return (dp[a]-2*sz[a] > dp[b]-2*sz[b]);
}

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v != p)
		{
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

void solve(int u, int p)
{
	dp[u] = max(tt[u], 2*(sz[u]-1));

	for (auto v: grafo[u])
		if (v != p)
			solve(v, u);
	
	sort(grafo[u].begin(), grafo[u].end(), comp);

	int soma = 0;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dp[u] = max(dp[u], 2*soma+dp[v]+1);
		soma += sz[v];
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &tt[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);
	solve(1, 0);

	printf("%d\n", max(dp[1], tt[1]+2*(n-1)));
}
