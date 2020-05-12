// Seletiva IOI 2018 - Polícia e Ladrão
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

struct Query
{
	int v, ind;
};

int n, q;

int nivel[maxn];
int st[maxn], en[maxn], back[maxn], tt;

int tab[maxn][20];

int tree[4*maxn], lazy[4*maxn];

int ans[maxn];

vector<Query> qry[maxn];
vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt, back[tt] = u;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		tab[v][0] = u;
		dfs(v, u);
	}

	en[u] = tt;
}

void build_lca(void)
{
	for (int j = 1; j <= 19; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = 19; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = 19; i >= 0; i--)
		if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return tab[u][0];
}

int kth(int u, int k)
{
	for (int i = 19; i >= 0; i--)
		if (k >= (1<<i))
			u = tab[u][i], k -= (1<<i);

	return u;
}

int dist(int u, int v)
{
	return (nivel[u]+nivel[v]-2*nivel[lca(u, v)]);
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = nivel[back[l]];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void flush(int node, int l, int r)
{
	if (lazy[node] == 0) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node] += lazy[node];
	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

void solve(int u, int p)
{
	for (auto Q: qry[u])
	{
		int v = Q.v, ind = Q.ind;
		int l = lca(u, v);
		int mid = (dist(v, u)-1)/2;

		if (nivel[v] >= nivel[u])
		{
			int k = kth(v, mid);

			ans[ind] = 2*query(1, 1, n, st[k], en[k]);
		}
		else
		{
			int k = kth(u, dist(u, l) - (mid - dist(v, l))-1);

			upd(1, 1, n, st[k], en[k], -inf);

			ans[ind] = 2*query(1, 1, n, 1, n);

			upd(1, 1, n, st[k], en[k], inf);
		}
	}

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		upd(1, 1, n, 1, n, 1);
		upd(1, 1, n, st[v], en[v], -2);

		solve(v, u);

		upd(1, 1, n, 1, n, -1);
		upd(1, 1, n, st[v], en[v], 2);
	}
}

int main(void)
{
	scanf("%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);
	build_lca();
	build(1, 1, n);

	for (int i = 1; i <= q; i++)
	{
		int c, d;

		scanf("%d %d", &c, &d);

		qry[c].push_back({d, i});
	}

	solve(1, 0);

	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
