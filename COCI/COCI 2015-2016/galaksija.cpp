// COCI 2015/2016 - Galaksija
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

int path[maxn];

struct Edge
{
	int u, v, w;
} edge[maxn];

struct DSU
{
	ll pairs;
	vector<int> pai, peso, elements[maxn];
	map<int, int> qtd[maxn];

	DSU(){}

	DSU(int n)
	{
		pai.resize(n+1); peso.resize(n+1);
		pairs = 0;

		for (int i = 1; i <= n; i++)
		{
			pai[i] = i, peso[i] = 1;
			qtd[i][0] = 1, elements[i].push_back(i);
		}
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Merge(int x, int y, int w)
	{
		for (auto v: qtd[y])
			pairs += 1ll*qtd[x][v.first^w]*v.second;

		for (auto v: qtd[y])
			qtd[x][v.first^w] += v.second;

		for (auto v: elements[y])
		{
			elements[x].push_back(v);

			path[v] ^= w;
		}

		qtd[y].clear(); elements[y].clear();
	}

	void Join(int x, int y, int w)
	{
		int old_x = x, old_y = y;
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y), swap(old_x, old_y);

		pai[y] = x, peso[x] += peso[y];

		Merge(x, y, w^path[old_x]^path[old_y]);
	}
} dsu;

int ord[maxn];

ll ans[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		edge[i] = {u, v, w};
	}

	for (int i = 1; i < n; i++)
		scanf("%d", &ord[i]);

	dsu = DSU(n);

	for (int i = n-1; i >= 1; i--)
	{
		int u = edge[ord[i]].u, v = edge[ord[i]].v, w = edge[ord[i]].w;

		dsu.Join(u, v, w);

		ans[i] = dsu.pairs;
	}

	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
}
