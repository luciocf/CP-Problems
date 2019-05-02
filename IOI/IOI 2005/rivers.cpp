// IOI 2005 - Rivers
// Lúcio Cardoso

// Solution:

// 1. Let's calculate dp(u, anc, x), where u is the subtree on which we want to calculate the minimum
// possible cost, assuming the closest ancestor 'u' can reach is 'anc' and it's possible to use x sawmills.

// 2. To calculate, assume u's subtrees are u_1, u_2, ..., u_t. We can use another DP aux[][] with two states,
// (l, S), which calculates the minimum cost using S (1 <= S <= k) sawmills on subtrees u_1, ..., u_l. It's simple to calculate it in 
// O(k^2) - if we use a sawmill on the root of u_l, then aux[l][S] = aux[l-1][S-j] + dp[u_l][u_l][j-1] (0 <= j <= S). Otherwise, 
// we have that aux[l][S] = aux[l-1][S-j] + dp[u_l][anc][j]. Also, in the end, dp[u][anc][S] = aux[deg(v)][S] + dist(u, anc).

// 3. The overall complexity will be O(n^2 * k^2). That's true because for each state on subtree u with ancestor anc, 
// we calculate a dp with K states and K transitions deg(u) times. Hence, the complexity. Notice the third state 'x' in the main DP
// doesn't affect the overall complexity.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;
const int maxk = 55;
const int inf = 2e9;

typedef pair<int, int> pii;

int n, k;
int w[maxn], dist[maxn];

int dp[maxn][maxn][maxk];

vector<pii> grafo[maxn];

void dfs(int u)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first, d = pp.second;

		dist[v] = dist[u]+d;
		dfs(v);
	}
}

int solve(int u, int anc, int x)
{
	if (grafo[u].size() == 0) return w[u]*(dist[u]-dist[anc]);
	if (dp[u][anc][x] != inf) return dp[u][anc][x];

	int add = w[u]*(dist[u]-dist[anc]);

	int aux[maxn][maxk];

	for (int l = 0; l <= k; l++)
		aux[0][l] = 0;

	for (int i = 1; i <= grafo[u].size(); i++)
	{
		int v = grafo[u][i-1].first;

		for (int l = 0; l <= k; l++)
		{
			aux[i][l] = inf;

			for (int j = 0; j <= l; j++)
			{
				if (j > 0) aux[i][l] = min(aux[i][l], aux[i-1][l-j]+solve(v, v, j-1));

				aux[i][l] = min(aux[i][l], aux[i-1][l-j]+solve(v, anc, j));

				if (i == grafo[u].size())
					dp[u][anc][l] = min(dp[u][anc][l], aux[i][l]+add);
			}
		}
	}

	return dp[u][anc][x];
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		int v, d;
		scanf("%d %d %d", &w[i], &v, &d);

		grafo[v].push_back({i, d});
	}

	dfs(0);

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for (int l = 0; l <= k; l++)
				dp[i][j][l] = inf;

	printf("%d\n", solve(0, 0, k));
}
