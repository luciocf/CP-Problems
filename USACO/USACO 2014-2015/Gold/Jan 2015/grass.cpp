// USACO Gold Jan 2015 - Grass Cownoisseur
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n, m;

int in[maxn], low[maxn], tt;
int scc[maxn], qtd[maxn], cc;

int dp[2][maxn];

bool mark[maxn];
bool reach[maxn];

vector<int> grafo[maxn];
vector<int> dag[maxn], dagT[maxn], topsort;

stack<int> stk;

void tarjan(int u)
{
	in[u] = low[u] = ++tt;
	stk.push(u);

	for (auto v: grafo[u])
	{
		if (in[v])
		{
			low[u] = min(low[u], in[v]);
			continue;
		}

		tarjan(v);

		low[u] = min(low[u], low[v]);
	}

	if (in[u] == low[u])
	{
		++cc;

		while (true)
		{
			int v = stk.top(); stk.pop();

			scc[v] = cc, in[v] = inf;

			qtd[cc]++;

			if (v == u) return;
		}
	}
}

void dfs(int u)
{
	reach[u] = true, mark[u] = true;

	for (auto v: dagT[u])
		if (!mark[v])
			dfs(v);
}

void dfs2(int u)
{
	mark[u] = true;

	for (auto v: dag[u])
		if (!mark[v])
			dfs2(v);

	topsort.push_back(u);
}

int main(void)
{
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
	}

	for (int i = 1; i <= n; i++)
		if (!in[i])
			tarjan(i);

	for (int u = 1; u <= n; u++)
	{
		for (auto v: grafo[u])
		{
			if (scc[u] != scc[v])
			{
				dag[scc[u]].push_back(scc[v]);
				dagT[scc[v]].push_back(scc[u]);
			}
		}
	}

	// check who reaches 1
	dfs(scc[1]);

	memset(mark, 0, sizeof mark);

	// get topsort
	for (int i = 1; i <= cc; i++)
		if (!mark[i])
			dfs2(i);

	dp[1][scc[1]] = qtd[scc[1]];

	for (auto u: topsort)
		for (auto v: dag[u])
			if (dp[1][v])
				dp[1][u] = max(dp[1][u], qtd[u]+dp[1][v]);

	reverse(topsort.begin(), topsort.end());

	dp[0][scc[1]] = qtd[scc[1]];

	for (auto u: topsort)
		for (auto v: dagT[u])
			if (dp[0][v])
				dp[0][u] = max(dp[0][u], qtd[u]+dp[0][v]);

	int ans = 0;

	for (int u = 1; u <= cc; u++)
		for (auto v: dagT[u])
			if (dp[0][u] && dp[1][v] && reach[v])
				ans = max(ans, dp[0][u]+dp[1][v]);

	printf("%d\n", ans-qtd[scc[1]]);
}
