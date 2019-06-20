// USACO Gold Jan 2018 - Cow at Large
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int sub[maxn], leaf[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p, int lvl)
{
	if (grafo[u].size() == 1)
		leaf[u] = 0;
	else
		leaf[u] = inf;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u, lvl+1);

		leaf[u] = min(leaf[u], 1+leaf[v]);
	}

	if (lvl >= leaf[u])
		sub[u] = 1;
	else
	{
		for (auto v: grafo[u])
			if (v != p)
				sub[u] += sub[v];
	}
}

int main(void)
{
	FILE *fin = fopen("atlarge.in", "r");
	FILE *fout = fopen("atlarge.out", "w");

	int n, k;
	fscanf(fin, "%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(k, 0, 0);

	fprintf(fout, "%d\n", sub[k]);
}
