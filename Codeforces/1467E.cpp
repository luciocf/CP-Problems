// Codeforces 1467E - Distinctive Roots in a Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int n;
int a[maxn];

int st[maxn], en[maxn], tt;

vector<int> grafo[maxn];
vector<pii> lista[maxn];

bool bad_down[maxn], bad_up[maxn];

struct BinaryLifting
{
	int tab[maxn][20], nivel[maxn];

	void dfs(int u, int p)
	{
		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u;
			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int j = 1; j < 20; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int kth(int u, int k)
	{
		for (int i = 19; i >= 0; i--)
			if (k >= (1<<i))
				u = tab[u][i], k -= (1<<i);

		return u;
	}
} LCA;

struct SegmentTree
{
	ll tree[4*maxn], lazy[4*maxn];

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r)
			lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

		tree[node] += 1ll*(r-l+1)*lazy[node];
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

		tree[node] = tree[2*node] + tree[2*node+1];
	}

	int query(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[node];

		int mid = (l+r)>>1;

		return query(2*node, l, mid, a, b) + query(2*node+1, mid+1, r, a, b);
	}
} seg;

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]];
}

bool inside(int u, int v)
{
	return (st[u] >= st[v] && en[u] <= en[v]);
}

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	en[u] = tt;
	lista[a[u]].push_back({st[u], u});
}

void doit(int u, int v)
{
	if (inside(v, u)) swap(u, v);

	if (!inside(u, v))
	{
		seg.upd(1, 1, n, st[u], en[u], 1);
		seg.upd(1, 1, n, st[v], en[v], 1);
	}
	else
	{
		seg.upd(1, 1, n, st[u], en[u], 1);
		seg.upd(1, 1, n, 1, n, 1);

		int k = LCA.nivel[u]-LCA.nivel[v]-1;
		int w = LCA.kth(u, k);

		seg.upd(1, 1, n, st[w], en[w], -1);
	}
}

void dfs_down(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			dfs_down(v, u);
			bad_down[u] |= bad_down[v];
		}
	}
 
	auto it = upper_bound(lista[a[u]].begin(), lista[a[u]].end(), make_pair(st[u], inf));
 
	if (it != lista[a[u]].end() && inside(it->ss, u))
		bad_down[u] = 1;
}

void dfs_up(int u, int p)
{
	int ind = 0, qtd = 0;

	for (auto v: grafo[u])
		if (v != p && bad_down[v])
			ind = v, ++qtd;

	if (qtd > 1 || bad_up[u])
	{
		for (auto v: grafo[u])
			if (v != p)
				bad_up[v] = 1;
	}
	else if (qtd == 1)
	{
		for (auto v: grafo[u])
			if (v != p && v != ind)
				bad_up[v] = 1;
	}

	for (auto v: grafo[u])
		if (v != p)
			dfs_up(v, u);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	compress();

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);
	LCA.dfs(1, 0); LCA.build();

	for (int i = 1; i <= n; i++)
		sort(lista[i].begin(), lista[i].end());

	for (int i = 1; i <= n; i++)
	{	
		if (lista[a[i]][0].ss != i) doit(i, lista[a[i]][0].ss);
		if (lista[a[i]].back().ss != i) doit(i, lista[a[i]].back().ss);
	}

	dfs_down(1, 0);
	dfs_up(1, 0);

	int ans = 0;

	for (int i = 1; i <= n; i++)
		if (seg.query(1, 1, n, st[i], st[i]) == 0 && !bad_down[i] && !bad_up[i])
			ans++;


	printf("%d\n", ans);
}
