// BOI 2013 - Pipes
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;
typedef pair<int, int> pii;

int n, m;

int c[maxn];

int ans[maxn];

int pai[maxn], nivel[maxn], edgePai[maxn];

int firstCycle=-1, lastCycle=-1, lastEdge=-1;

bool mark[maxn], inCycle[maxn], ok=1;

vector<pii> grafo[maxn];

void dfs(int u, int p)
{
	mark[u] = true;

	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;

		if (mark[v])
		{
			if (v == p) continue;

			firstCycle = u, lastCycle = v, lastEdge = e;

			if (abs(nivel[u]-nivel[v])%2 == 1)
				ok = 0;

			continue;
		}

		pai[v] = u, nivel[v] = nivel[u]+1, edgePai[v] = e;

		dfs(v, u);
	}
}

void markCycle(void)
{
	if (firstCycle == -1) return;

	int v = lastCycle;

	while (true)
	{
		inCycle[v] = true;

		if (v == firstCycle) break;

		v = pai[v];
	}
}

void solve(int u)
{
	mark[u] = true;

	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;

		if (mark[v]) continue;

		solve(v);

		if (!inCycle[v])
		{
			ans[e] = 2*c[v];
			c[u] -= ans[e]/2, c[v] = 0;
		}
	}
}

void solveCycle(void)
{
	if (firstCycle == -1) return;

	int v = lastCycle, sign = 1;
	ll sum = 0ll;

	while (true)
	{
		sum += 1ll*sign*c[v];

		if (v == firstCycle) break;

		sign *= -1, v = pai[v];
	}

	ans[lastEdge] = sum;

	int prev = ans[lastEdge];
	v = lastCycle;

	while (v != firstCycle)
	{
		int e = edgePai[v];

		ans[e] = 2*c[v] - prev;

		v = pai[v], prev = ans[e];
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});
	}

	if (m > n)
	{
		printf("0\n");
		return 0;
	}

	dfs(1, 0);

	if (!ok)
	{
		printf("0\n");
		return 0;
	}

	markCycle();

	memset(mark, 0, sizeof mark);

	if (firstCycle == -1)
		solve(1);
	else
		solve(firstCycle);

	solveCycle();

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
