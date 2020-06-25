// Codeforces 915F - Imbalance Value of a Tree
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;

struct DSU
{
	int pai[maxn], peso[maxn];

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

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
	}
};

int a[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

bool comp(int x, int y) {return a[x] < a[y];}

bool comp2(int x, int y) {return a[x] > a[y];}

int main(void)
{
	int n;
	scanf("%d", &n);

	DSU dsu;
	dsu.init(n);

	vector<int> lista;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		lista.push_back(i);
	}

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	sort(lista.begin(), lista.end(), comp);

	ll ans = 0;

	for (auto u: lista)
	{
		mark[u] = true;

		vector<int> pref, sz;

		int soma = 0;

		for (auto v: grafo[u])
		{
			if (mark[v])
			{
				soma += dsu.peso[dsu.Find(v)];

				sz.push_back(dsu.peso[dsu.Find(v)]);
				pref.push_back(soma);
			}
		}

		for (auto v: grafo[u])
			if (mark[v])
				dsu.Join(u, v);

		if (pref.size() == 0)
		{
			ans += 1ll*a[u];
			continue;
		}

		ans += 1ll*a[u]*(pref.back()+1);

		for (int i = 1; i < pref.size(); i++)
			ans += 1ll*a[u]*sz[i]*pref[i-1];
	}

	dsu.init(n);
	memset(mark, 0, sizeof mark);

	sort(lista.begin(), lista.end(), comp2);

	for (auto u: lista)
	{
		mark[u] = true;

		vector<int> pref, sz;

		int soma = 0;

		for (auto v: grafo[u])
		{
			if (mark[v])
			{
				soma += dsu.peso[dsu.Find(v)];

				sz.push_back(dsu.peso[dsu.Find(v)]);
				pref.push_back(soma);
			}
		}

		for (auto v: grafo[u])
			if (mark[v])
				dsu.Join(u, v);

		if (sz.size() == 0)
		{
			ans -= 1ll*a[u];
			continue;
		}

		ans -= 1ll*a[u]*(pref.back()+1);

		for (int i = 1; i < pref.size(); i++)
			ans -= 1ll*a[u]*sz[i]*pref[i-1];
	}

	printf("%lld\n", ans);
}
