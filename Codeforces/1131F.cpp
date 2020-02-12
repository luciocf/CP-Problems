// Codeforces 1131F - Asya And Kittens
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int pai[maxn], peso[maxn];

int ponta[2][maxn];

int pai_linha[maxn];

void init(int n)
{
	for (int i = 1; i <= n; i++)
	{
		pai[i] = i, peso[i] = 1;
		ponta[0][i] = ponta[1][i] = i;
	}
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];

	pai_linha[ponta[1][y]]  = ponta[0][x];

	ponta[0][x] = ponta[0][y];
}

int main(void)
{
	int n;
	scanf("%d", &n);

	init(n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		Join(u, v);
	}

	int v;
	for (int i = 1; i <= n; i++)
		if (ponta[0][Find(1)] == i)
			v = i;

	printf("%d", v);
	while (v != ponta[1][Find(1)])
	{
		printf(" %d", pai_linha[v]);
		v = pai_linha[v];
	}
	printf("\n");
}
