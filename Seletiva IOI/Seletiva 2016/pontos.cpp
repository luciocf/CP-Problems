// Seletiva IOI 2016 - Pontos
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

struct Pt
{
	int x, y, z;
} pt[maxn];

struct UF
{
	int pai_x, peso_x, mx_x[8];
	int pai_y, peso_y, mx_y[8];
};

int n;

int pai[maxn], peso[maxn], mx[maxn][8];

stack<UF> stk;

void init(void)
{
	for (int i = 1; i <= n; i++)
	{
		pai[i] = i, peso[i] = 1;

		for (int mask = 0; mask < 8; mask++)
		{
			if (mask&(1<<0)) mx[i][mask] += pt[i].x;
			else mx[i][mask] -= pt[i].x;

			if (mask&(1<<1)) mx[i][mask] += pt[i].y;
			else mx[i][mask] -= pt[i].y;

			if (mask&(1<<2)) mx[i][mask] += pt[i].z;
			else mx[i][mask] -= pt[i].z;
		}
	}
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return Find(pai[x]);
}

void Store(int x, int y)
{
	UF uf;

	uf.pai_x = x, uf.peso_x = peso[x];
	uf.pai_y = y, uf.peso_y = peso[y];

	for (int i = 0; i < 8; i++)
	{
		uf.mx_x[i] = mx[x][i];
		uf.mx_y[i] = mx[y][i];
	}

	stk.push(uf);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	Store(x, y);

	pai[y] = x, peso[x] += peso[y];
	for (int i = 0; i < 8; i++)
		mx[x][i] = max(mx[x][i], mx[y][i]);
}

void Rollback(void)
{
	UF uf = stk.top(); stk.pop();

	int x = uf.pai_x, y = uf.pai_y;
	int peso_x = uf.peso_x, peso_y = uf.peso_y;

	pai[x] = x, pai[y] = y;
	peso[x] = peso_x, peso[y] = peso_y;

	for (int i = 0; i < 8; i++)
	{
		mx[x][i] = uf.mx_x[i];
		mx[y][i] = uf.mx_y[i];
	} 
}

int Query(int x, int y)
{
	x = Find(x), y = Find(y);

	int ans = 0;

	for (int i = 0; i < 8; i++)
	{
		int mask1 = i, mask2 = i^7;

		ans = max(ans, mx[x][mask1]+mx[y][mask2]);
	}

	return ans;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &pt[i].x, &pt[i].y, &pt[i].z);

	init();

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int x, y;
			scanf("%d %d", &x, &y);

			Join(x, y);
		}
		else if (op == 2) Rollback();
		else
		{
			int x, y;
			scanf("%d %d", &x, &y);

			printf("%d\n", Query(x, y));
		}
	}
}
