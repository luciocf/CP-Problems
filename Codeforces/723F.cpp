// Codeforces 723F - st-Spanning Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int n;

int pai[maxn], peso[maxn];

bool mark[2][maxn];

vector<int> grafo[maxn];

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

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	init();

	int s, t, ds, dt;
	scanf("%d %d %d %d", &s, &t, &ds, &dt);

	vector<pii> edge;

	for (int i = 1; i <= n; i++)
	{
		for (auto v: grafo[i])
		{
			if (i != s && i != t && v != s && v != t && Find(i) != Find(v))
			{
				Join(i, v);
				edge.push_back({i, v});
			}
		}
	}

	mark[0][s] = 1;
	for (auto v: grafo[s])
		mark[0][Find(v)] = 1;

	mark[1][t] = 1;
	for (auto v: grafo[t])
		mark[1][Find(v)] = 1;

	for (auto v: grafo[s])
	{
		if (!mark[1][Find(v)] && Find(v) != Find(s))
		{
			Join(v, s), ds--;
			edge.push_back({v, s});
		}
	}

	for (auto v: grafo[t])
	{
		if (!mark[0][Find(v)] && Find(v) != Find(t))
		{
			Join(v, t), dt--;
			edge.push_back({v, t});
		}
	}

	if (ds < 0 || dt < 0)
	{
		printf("No\n");
		return 0;
	}

	for (auto v: grafo[s])
	{
		if (Find(v) != Find(s) && ds > 0 && v != t)
		{
			Join(v, s), ds--;
			if (v == t) dt--;
			edge.push_back({v, s});
		}
	}

	for (auto v: grafo[t])
	{
		if (Find(v) != Find(t) && Find(v) != Find(s) && dt > 0)
		{
			Join(v, t), dt--;
			edge.push_back({v, t});
		}
	}

	for (auto v: grafo[s])
	{
		if (Find(v) != Find(s) && ds > 0 && (v != t || dt > 0))
		{
			Join(v, s), ds--;
			if (v == t) dt--;
			edge.push_back({v, s});
		}
	}

	for (auto v: grafo[t])
	{
		if (Find(v) != Find(t) && dt > 0 && (v != s || ds > 0))
		{
			Join(v, t), dt--;
			if (v == s) ds--;
			edge.push_back({v, t});
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (Find(i) != Find(1))
		{
			printf("No\n");
			return 0;
		}
	}

	printf("Yes\n");
	for (auto e: edge)
		printf("%d %d\n", e.first, e.second);
}
