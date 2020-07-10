// Codeforces 1166F - Vicky's Delivery Service
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

struct DSU
{
	int pai[maxn], peso[maxn];
	set<int> out[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Merge(int x, int y)
	{
		if (out[x].size() >= out[y].size())
		{
			for (auto v: out[y])
				out[x].insert(v);
		}
		else
		{
			for (auto v: out[x])
				out[y].insert(v);

			swap(out[x], out[y]);
		}
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
		Merge(x, y);
	}
} dsu;

map<int, int> cor[maxn];

void add(int u, int v, int w)
{
	dsu.out[dsu.Find(u)].insert(v);
	dsu.out[dsu.Find(v)].insert(u);

	if (cor[u].find(w) != cor[u].end())
		dsu.Join(v, cor[u][w]);

	if (cor[v].find(w) != cor[v].end())
		dsu.Join(u, cor[v][w]);

	cor[u][w] = v;
	cor[v][w] = u;
}

void query(int u, int v)
{
	if (dsu.Find(u) == dsu.Find(v) || dsu.out[dsu.Find(u)].find(v) != dsu.out[dsu.Find(u)].end()) printf("Yes\n");
	else printf("No\n");
}

int main(void)
{
	int n, m, c, q;
	scanf("%d %d %d %d", &n, &m, &c, &q);

	dsu.init(n);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		add(u, v, w);
	}

	while (q--)
	{
		char op;
		scanf(" %c", &op);

		if (op == '+')
		{
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);

			add(u, v, w);
		}
		else
		{
			int u, v;
			scanf("%d %d", &u, &v);

			query(u, v);
		}
	}
}
