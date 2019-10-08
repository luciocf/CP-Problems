// COCI 2016/2017 - Burza
// Lúcio Cardoso

// Solution: http://hsin.hr/coci/archive/2016_2017/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 410;

int n, k;
int nivel[maxn];

int ini[maxn], fim[maxn], tt;

bool dp[maxn][1<<20];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	if (nivel[u] == k)
	{
		ini[u] = ++tt;
		fim[u] = tt;
		return;
	}

	ini[u] = n+1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		dfs(v, u);

		ini[u] = min(ini[u], ini[v]);
		fim[u] = max(fim[u], fim[v]);
	}
}

void dfs2(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		if (nivel[v] != k)
			dfs2(v, u);

		for (int mask = 0; mask < (1<<(k+1)); mask++)
			if (!(mask&(1<<nivel[v])))
				dp[fim[v]][mask|(1<<nivel[v])] |= dp[ini[v]-1][mask];
	}
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	if (k >= 20)
	{
		printf("DA\n");
		return 0;
	}

	dfs(1, 0);

	if (tt == 0)
	{
		printf("DA\n");
		return 0;
	}

	for (int mask = 0; mask < (1<<(k+1)); mask++)
		dp[0][mask] = 1;

	dfs2(1, 0);

	bool ok = 0;
	for (int mask = 0; mask < (1<<(k+1)); mask++)
		ok |= dp[tt][mask];

	if (ok) printf("DA\n");
	else printf("NE\n");
}
