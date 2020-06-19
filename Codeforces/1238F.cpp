// Codeforces 1238F - The Maximum Subtree
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

int dp[maxn][2];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	pii mx = {0, 0};
	int tot = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;
		++tot;

		dfs(v, u);

		if (dp[v][0] > mx.ff) mx.ss = mx.ff, mx.ff = dp[v][0];
		else if (dp[v][0] > mx.ss) mx.ss = dp[v][0];
	}

	int tot1 = tot, tot2 = tot;

	if (p) tot1++;

	dp[u][0] = tot2, dp[u][1] = tot1;

	if (mx.ss) dp[u][1] = max(dp[u][1], mx.ff + mx.ss + tot1-2);
	else if (mx.ff) dp[u][1] = max(dp[u][1], mx.ff + tot1-1);

	if (mx.ff) dp[u][0] = max(dp[u][0], mx.ff + tot2-1);
}

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			grafo[i].clear();

		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}

		if (n <= 2)
		{
			printf("%d\n", n);
			continue;
		}

		int root;
		for (int i = 1; i <= n; i++)
			if (grafo[i].size() > 1)
				root = i;

		dfs(root, 0);

		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans = max(ans, dp[i][1]);

		printf("%d\n", ans);
	}
}
