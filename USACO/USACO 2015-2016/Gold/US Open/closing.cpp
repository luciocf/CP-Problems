// USACO Gold US Open 2016 - Closing the Farm
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int pai[maxn], peso[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

int query[maxn];

bool ans[maxn];
bool mark[maxn];

vector<int> grafo[maxn];

int main(void)
{
	FILE *fin = fopen("closing.in", "r");
	FILE *fout = fopen("closing.out", "w");

	int m;
	fscanf(fin, "%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	init();

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &query[i]);

	int root = query[n];
	ans[n] = 1, mark[root] = 1;

	for (int i = n-1; i >= 1; i--)
	{
		int u = query[i];
		mark[u] = 1;

		for (auto v: grafo[u])
			if (mark[v])
				Join(u, v);

		if (peso[Find(root)] == n-i+1)
			ans[i] = 1;
	}

	for (int i = 1; i <= n; i++)
	{
		if (ans[i]) fprintf(fout, "YES\n");
		else fprintf(fout, "NO\n");
	}
}
