// COCI 2014-2015 - Uzastopni
// Lúcio Cardoso

// Solution:

// 1. Let S_u_l be the set of all possible intervals using only vertices
// in the subtree of u such that the smallest joke is l.

// 2. Then, for all r >= l such that one of u's children has the interval [l, r],
// we have that S_u_l = S_u_l union S_u_(r+1).

// 3. We can do this in O((n*v^3)/32) by using bitsets to represents the sets
// S_u_l.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;
const int maxv = 110;

int a[maxn];

bool tem[maxv][maxv];

vector<int> grafo[maxn];

bitset<maxv> bs[maxn][maxv];

void undo(void)
{
	for (int i = 1; i < maxv; i++)
		for (int j = 1; j < maxv; j++)
			tem[i][j] = 0;
}

void dfs(int u, int p)
{
	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	undo();

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		for (int i = 1; i < maxv; i++)
		{
			for (int j = i; j < maxv; j++)
			{
				if (i > a[u] && i <= a[v] && bs[v][i][j]) bs[u][i][j] = 1;
				if (i <= a[v] && bs[v][i][j]) tem[i][j] = 1;
			}
		}
	}

	bs[u][a[u]][a[u]] = tem[a[u]][a[u]] = 1;

	for (int l = maxv-1; l > a[u]; l--)
		for (int r = l; r < maxv-1; r++)
			if (tem[l][r])
				bs[u][l] |= bs[u][r+1];

	bs[u][a[u]] |= bs[u][a[u]+1];

	for (int l = a[u]-1; l >= 1; l--)
		for (int r = l; r < a[u]; r++)
			if (tem[l][r])
				bs[u][l] |= bs[u][r+1]; 
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(1, 0);

	int ans = 0;
	for (int i = 1; i <= a[1]; i++)
		ans += (int)bs[1][i].count();

	printf("%d\n", ans);
}
