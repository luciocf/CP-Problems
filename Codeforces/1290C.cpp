// Codeforces 1290C - Prefix Enlightenment
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;
const int inf = 1e9+10;

int n, k, ans;
char a[maxn];

int pai[maxn], peso[maxn];
int qtd[maxn][2];

int cor[maxn];

int edge[maxn][2];

vector<int> comp[maxn];

void init(void)
{
	for (int i = 1; i <= k; i++)
	{
		pai[i] = i, peso[i] = qtd[i][0] = 1, cor[i] = 0;
		comp[i].push_back(i);
	}
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void merge(int x, int y, bool flag)
{
	for (auto v: comp[y])
	{
		if (flag) cor[v] = cor[v]^1;

		comp[x].push_back(v);
	}

	if (flag) swap(qtd[y][0], qtd[y][1]);

	qtd[x][0] += qtd[y][0];
	qtd[x][1] += qtd[y][1];

	qtd[x][0] = min(inf, qtd[x][0]);
	qtd[x][1] = min(inf, qtd[x][1]);
} 

// flag = 0 -> diferente
// flag = 1 -> igual
void Join(int x, int y, bool flag)
{
	int cx = cor[x], cy = cor[y];

	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	bool q;

	if (flag == 0)
	{
		if (cx != cy) q = 0;
		else q = 1;
	}
	else
	{
		if (cx != cy) q = 1;
		else q = 0;
	}

	ans -= min(qtd[x][0], qtd[x][1]);
	ans -= min(qtd[y][0], qtd[y][1]);

	merge(x, y, q);
	pai[y] = x, peso[x] += peso[y];

	ans += min(qtd[x][0], qtd[x][1]);
}

void Fix(int u, bool flag)
{
	int fu = Find(u);

	ans -= min(qtd[fu][0], qtd[fu][1]);

	if (flag == 0)
	{
		if (cor[u] == 0) qtd[fu][0] = inf;
		else qtd[fu][1] = inf;
	}
	else
	{
		if (cor[u] == 1) qtd[fu][0] = inf;
		else qtd[fu][1] = inf;
	}

	ans += min(qtd[fu][0], qtd[fu][1]);
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf(" %c", &a[i]);

	for (int i = 1; i <= k; i++)
	{
		int m;
		scanf("%d", &m);

		for (int j = 1; j <= m; j++)
		{
			int v;
			scanf("%d", &v);

			if (edge[v][0] == 0) edge[v][0] = i;
			else edge[v][1] = i;
		}
	}

	init();

	for (int i = 1; i <= n; i++)
	{
		if (edge[i][1]) Join(edge[i][0], edge[i][1], (int)(a[i]-'0'));
		else Fix(edge[i][0], 1-(int)(a[i]-'0'));

		printf("%d\n", ans);
	}
}
