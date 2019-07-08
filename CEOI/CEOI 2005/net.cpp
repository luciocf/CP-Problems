// CEOI 2005 - Critical Network Lines
// Lúcio Cardoso

// Solution:

// 1. Critical lines are bridges. Thus, find the bridge tree of the graph. 

// 2. A critical line is a bridge such that by my removing it, the amount of As or Bs in one of the
// two components made in the tree have is equal to 0. We can check that with a DFS.

// Complexity: O(n+m)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxm = 1e6+10;

typedef pair<int, int> pii;

int n, m, K, L;

int in[maxn], low[maxn], tt;

int cc, bcc[maxn], qtd[2][maxn], sub[2][maxn];

bool isA[maxn], isB[maxn];
bool bridge[maxm], critic[maxm];

pair<int, int> edge[maxm];

vector<pii> grafo[maxn], tree[maxn];

void dfsBridge(int u, int p)
{
	in[u] = low[u] = ++tt;

	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;

		if (in[v])
		{
			if (v != p)
				low[u] = min(low[u], in[v]);

			continue;
		}

		dfsBridge(v, u);

		if (low[v] > in[u])
			bridge[e] = true;

		low[u] = min(low[u], low[v]);
	}
}

void dfsCalc(int u, int p, int edgeP)
{
	sub[0][u] += qtd[0][u];
	sub[1][u] += qtd[1][u];

	for (auto pp: tree[u])
	{
		int v = pp.first, e = pp.second;

		if (v == p) continue;

		dfsCalc(v, u, e);

		sub[0][u] += sub[0][v];
		sub[1][u] += sub[1][v];
	}

	int fora0 = K-sub[0][u], fora1 = L-sub[1][u];

	if (edgeP && (!sub[0][u] || !sub[1][u] || !fora0 || !fora1))
		critic[edgeP] = true;
}

void fill(int u)
{
	bcc[u] = cc;

	for (auto v: grafo[u])
		if (!bcc[v.first] && !bridge[v.second])
			fill(v.first);
}

int main(void)
{
	scanf("%d %d %d %d", &n, &m, &K, &L);

	for (int i = 1; i <= K; i++)
	{
		int u;
		scanf("%d", &u);

		isA[u] = true;
	}

	for (int i = 1; i <= L; i++)
	{
		int u;
		scanf("%d", &u);

		isB[u] = true;
	}

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});

		edge[i] = {u, v};
	}

	dfsBridge(1, 0);

	for (int i = 1; i <= n; i++)
	{
		if (!bcc[i])
		{
			++cc;
			fill(i);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (isA[i]) qtd[0][bcc[i]]++;
		if (isB[i]) qtd[1][bcc[i]]++;
	}

	for (int i = 1; i <= n; i++)
		for (auto pp: grafo[i])
			if (bridge[pp.second])
				tree[bcc[i]].push_back({bcc[pp.first], pp.second});

	dfsCalc(1, 0, 0);

	int tot = 0;
	vector<pii> ans;

	for (int i = 1; i <= m; i++)
		if (critic[i])
			tot++, ans.push_back(edge[i]);

	printf("%d\n", tot);
	for (auto pp: ans)
		printf("%d %d\n", pp.first, pp.second);
}

/*
	* bounds (maxn)
	* long long
	* all variables reset?
	* check if indexing is ok
	* off by one? (n-i+1) or (n-i)?
	* edge cases (n=0, n=1, n < 0, n=maxn)
*/
