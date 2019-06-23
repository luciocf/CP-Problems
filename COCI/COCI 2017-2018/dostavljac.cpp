// COCI 2017-2018 - Dostavljac
// Lúcio Cardoso

// Solution:

// 1. Let dp[0][u][k] be the greatest amount we can achieve by starting our path at vertex u and
// finishing it inside the subtree of u, using a cost k. Similarly, let dp[1][u][k] be the same as
// the greatest amount in a path starting at u and ending at u with a cost of k.

// 2. At first, dp[0][u][k] = dp[1][u][k] = A[k], for all k > 0. Then, we can use "knapsack on trees".
// For each child v of u, we have:

// * dp[0][u][k] = max(dp[0][u][k], max(dp[0][v][j], dp[1][v][j]) + dp[1][u][i-j-1]), for 0 <= j < k (we end our path inside the subtree of v)
// * dp[0][u][k] = max(dp[0][u][k], dp[1][v][j] + dp[0][u][i-j-2]), for 0 <= j < k-1 (we end our path inside the subtree of another child)
// * dp[1][u][k] = max(dp[1][u][k], dp[1][v][j] + dp[1][u][i-j-2]), for 0 <= j < k-1 (we can go through v's subtree)

// 3. Final answer is max(dp[0][1][m], dp[1][1][m]). Overall complexity if O(n*m^2).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;

int n, m;
int A[maxn];

// 0 - ending inside subtree
// 1 - coming back to vertex
int dp[2][maxn][maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (int i = 1; i <= m; i++)
		dp[0][u][i] = dp[1][u][i] = A[u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		for (int i = m; i >= 1; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				if (i >= j+1)
					dp[0][u][i] = max(dp[0][u][i], max(dp[0][v][j], dp[1][v][j]) + dp[1][u][i-j-1]);
				if (i >= j+2)
				{
					dp[0][u][i] = max(dp[0][u][i], dp[1][v][j] + dp[0][u][i-j-2]);
					dp[1][u][i] = max(dp[1][u][i], dp[1][v][j] + dp[1][u][i-j-2]);
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &A[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(1, 0);

	printf("%d\n", max(dp[0][1][m], dp[1][1][m]));
}
