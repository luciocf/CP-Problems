// IOI 2018 - Werewolf
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "werewolf.h"

using namespace std;

const int maxn = 6e5+10;

int n;

struct Edge
{
	int u, v, w;
} edge[2][maxn];

struct DSU
{
	int pai[maxn];

	void init(void)
	{
		for (int i = 1; i < maxn; i++)
			pai[i] = i;
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

		pai[y] = x;
	}
} dsu;

struct BIT
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] += v;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans += bit[x];
		return ans;
	}

	int get(int l, int r)
	{
		return soma(r) - soma(l-1);
	}
} BIT;

struct Event
{
	int x, y1, y2, t, ind;

	bool operator <(const Event &o)
	{
		if (o.x == x) return t < o.t;
		return x < o.x;
	}
} event[maxn];

int val[2][maxn];

int st[2][maxn], en[2][maxn], tt;

int tab[2][maxn][20];

int ans[maxn];

vector<int> grafo[2][maxn];

void dfs(int u, int p, int q)
{
	st[q][u] = ++tt;

	for (auto v: grafo[q][u])
	{
		if (v != p)
		{
			tab[q][v][0] = u;

			dfs(v, u, q);
		}
	}

	en[q][u] = tt;
}

void build_tab(int q)
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i < maxn; i++)
			tab[q][i][j] = tab[q][tab[q][i][j-1]][j-1];
}

int get_menor(int u, int k)
{
	for (int i = 19; i >= 0; i--)
		if (val[0][tab[0][u][i]] >= k)
			u = tab[0][u][i];

	return u;
}

int get_maior(int u, int k)
{
	for (int i = 19; i >= 0; i--)
		if (tab[1][u][i] && val[1][tab[1][u][i]] <= k)
			u = tab[1][u][i];

	return u;
}

void build(int q, int m)
{
	dsu.init();

	int ind = n;

	for (int i = 1; i <= m; i++)
	{
		int u = dsu.Find(edge[q][i].u), v = dsu.Find(edge[q][i].v), w = edge[q][i].w;

		if (u != v)
		{
			++ind;
			val[q][ind] = w;

			dsu.Join(ind, u); dsu.Join(ind, v);

			grafo[q][ind].push_back(u); grafo[q][u].push_back(ind);
			grafo[q][ind].push_back(v); grafo[q][v].push_back(ind);
		}
	}

	tt = 0;
	dfs(dsu.Find(1), 0, q);
	build_tab(q);
}

void do_sweep(int q)
{
	sort(event+1, event+q+1);

	for (int i = 1; i <= q; i++)
	{
		auto E = event[i];

		if (E.t == 0) BIT.upd(E.y1, 1);
		else ans[E.ind] += (E.t == 1 ? -1 : 1)*BIT.get(E.y1, E.y2);
	}
}

vector<int> check_validity(int N, vector<int> X, vector<int> Y,
								vector<int> S, vector<int> E,
                                vector<int> L, vector<int> R)
{
	n = N;
	int m = 0;

	for (int i = 0; i < X.size(); i++)
	{
		edge[0][++m] = {X[i]+1, Y[i]+1, min(X[i]+1, Y[i]+1)};
		edge[1][m] = {X[i]+1, Y[i]+1, max(X[i]+1, Y[i]+1)};
	}

	sort(edge[0]+1, edge[0]+m+1, [&] (Edge a, Edge b) {return a.w > b.w;});
	build(0, m);

	sort(edge[1]+1, edge[1]+m+1, [&] (Edge a, Edge b) {return a.w < b.w;});
	build(1, m);

	int queries = 0;

	for (int i = 0; i < S.size(); i++)
	{
		int s = S[i]+1, e = E[i]+1, l = L[i]+1, r = R[i]+1;

		int u = get_menor(s, l);
		int v = get_maior(e, r);

		event[++queries] = {st[0][u]-1, st[1][v], en[1][v], 1, i+1};
		event[++queries] = {en[0][u], st[1][v], en[1][v], 2, i+1};
	}

	for (int i = 1; i <= n; i++)
		event[++queries] = {st[0][i], st[1][i], st[1][i], 0, 0};

	do_sweep(queries);

	vector<int> final;

	for (int i = 1; i <= S.size(); i++)
		final.push_back(ans[i] > 0);

	return final;
}
