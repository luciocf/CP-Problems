// APIO 2008 - Roads
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

struct Edge
{
	int u, v, w;
} edge[maxn];

int n, m, k;

int pai[maxn], peso[maxn];

vector<Edge> ans;

vector<pii> grafo[maxn];

bool comp1(Edge a, Edge b) {return a.w < b.w;}

bool comp2(Edge a, Edge b) {return a.w > b.w;}

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

bool get_zero(void)
{
	init();

	for (int i = 1; i <= m; i++)
		if (edge[i].w == 0 && Find(edge[i].u) != Find(edge[i].v))
			Join(edge[i].u, edge[i].v);

	for (int i = 1; i <= m; i++)
	{
		if (edge[i].w == 1 && Find(edge[i].u) != Find(edge[i].v))
		{
			Join(edge[i].u, edge[i].v);
			ans.push_back(edge[i]);
		}
	}

	for (int i = 1; i <= n; i++)
		if (Find(i) != Find(1))
			return false;

	return true;
}

bool get_one(void)
{
	init();

	for (int i = 1; i <= m; i++)
		if (edge[i].w == 1 && Find(edge[i].u) != Find(edge[i].v))
			Join(edge[i].u, edge[i].v);

	for (int i = 1; i <= m; i++)
	{
		if (edge[i].w == 0 && Find(edge[i].u) != Find(edge[i].v))
		{
			Join(edge[i].u, edge[i].v);
			ans.push_back(edge[i]);
		}
	}

	for (int i = 1; i <= n; i++)
		if (Find(i) != Find(1))
			return false;

	return true;
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	map<pii, bool> ord;

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		ord[{u, v}] = 1;

		edge[i] = {u, v, !w};
		grafo[u].push_back({v, !w}); grafo[v].push_back({u, !w});
	}

	if (!get_zero())
	{
		printf("no solution\n");
		return 0;
	}

	k -= (int)ans.size();

	if (k < 0)
	{
		printf("no solution\n");
		return 0;
	}

	if (!get_one())
	{
		printf("no solution\n");
		return 0;
	}

	init();
	for (auto e: ans)
		Join(e.u, e.v);

	int tot = 0;

	for (int i = 1; i <= m; i++)
	{
		if (tot == k) break;

		if (edge[i].w == 1 && Find(edge[i].u) != Find(edge[i].v))
		{
			Join(edge[i].u, edge[i].v);

			ans.push_back(edge[i]);
			++tot;
		}
	}

	if (tot != k)
	{
		printf("no solution\n");
		return 0;
	}

	for (int i = 1; i <= m; i++)
	{
		if (edge[i].w == 0 && Find(edge[i].u) != Find(edge[i].v))
		{
			Join(edge[i].u, edge[i].v);
			ans.push_back(edge[i]);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (Find(i) != Find(1))
		{
			printf("no solution\n");
			return 0;
		}
	}

	for (auto e: ans)
	{
		if (ord[{e.u, e.v}]) printf("%d %d %d\n", e.u, e.v, !e.w);
		else printf("%d %d %d\n", e.v, e.u, !e.w);
	}
}
