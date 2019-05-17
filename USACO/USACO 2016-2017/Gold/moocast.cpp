// USACO 2016-2017 - Moocast
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int n;
int x[maxn], y[maxn];

int pai[maxn], peso[maxn];

int dist(int a, int b)
{
	return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

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

bool ok(int x)
{
	init();

	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			if (dist(i, j) <= x)
				Join(i, j);

	return (peso[Find(1)] == n);
}

int busca(void)
{
	int ini = 0, fim = 2e9, ans = 2e9;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	FILE *fin = fopen("moocast.in", "r");
	FILE *fout = fopen("moocast.out", "w");

	fscanf(fin, "%d", &n);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d %d", &x[i], &y[i]);

	fprintf(fout, "%d\n", busca());
}
