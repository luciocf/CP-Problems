// USACO 2017-2018 - Mootube
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef pair<int, int> pii;

struct Q
{
	int u, k, ind;
} query[maxn];

struct E
{
	int u, v, w;
} edge[maxn];

int pai[maxn], peso[maxn];

int ans[maxn];

void Init(int n)
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

bool comp(Q a, Q b)
{
	return a.k > b.k;
}

bool comp2(E a, E b)
{
	return a.w > b.w;
}

int main(void)
{
	FILE *fin = fopen("mootube.in", "r");
	FILE *fout = fopen("mootube.out", "w");

	int n, q;
	fscanf(fin, "%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		fscanf(fin, "%d %d %d", &u, &v, &w);

		edge[i] = {u, v, w};
	}

	for (int i = 1; i <= q; i++)
	{
		fscanf(fin, "%d %d", &query[i].k, &query[i].u);
		query[i].ind = i;
	}

	sort(query+1, query+q+1, comp);
	sort(edge+1, edge+n, comp2);

	Init(n);

	int ant = 1;
	for (int i = 1; i <= q; i++)
	{
		int u = query[i].u, k = query[i].k;

		for (; edge[ant].w >= k && ant < n; ant++)
			Join(edge[ant].u, edge[ant].v);

		ans[query[i].ind] = peso[Find(u)]-1;
	}

	for (int i = 1; i <= q; i++)
		fprintf(fout, "%d\n", ans[i]);
}
