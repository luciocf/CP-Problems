// IOI 2014 - Game
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "game.h"

using namespace std;

const int maxn = 1510;

int N;
int pai[maxn], peso[maxn];
int relation[maxn][maxn];

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

	for (int i = 0; i < N; i++)
	{
		relation[x][i] += relation[y][i];
		relation[i][x] += relation[i][y];
	}
}

void initialize(int n) 
{
	N = n;
	for (int i = 0; i < n; i++)
	{
		pai[i] = i, peso[i] = 1;

		for (int j = 0; j < n; j++)
			if (i != j) relation[i][j] = 1;
	}
}

int hasEdge(int u, int v) 
{
	int cu = Find(u), cv = Find(v);

	if (relation[cu][cv] == 1)
	{
		Join(u, v);
		return 1;
	}

	relation[cu][cv]--, relation[cv][cu]--;

	return 0;
}
