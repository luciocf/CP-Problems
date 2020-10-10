// Codeforces 1062E - Company
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n;

int st[maxn], tt;
int nivel[maxn];

vector<int> grafo[maxn];

struct BinaryLifting
{
	int tab[maxn][20];

	void dfs(int u, int p)
	{
		st[u] = ++tt;

		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u;
			dfs(v, u);
		}
	}

	void build(int n)
	{
		for (int j = 1; j < 20; j++)
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
} LCA;

struct SegmentTree
{
	pii tree[2][3*maxn];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[0][node] = {st[l], l};
			tree[1][node] = {st[l], l};
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		tree[0][node] = max(tree[0][2*node], tree[0][2*node+1]);
		tree[1][node] = min(tree[1][2*node], tree[1][2*node+1]);
	}

	pii query(int node, int l, int r, int a, int b, int q)
	{
		if (l > b || r < a) return {(q == 0 ? -inf : inf), -inf};
		if (l >= a && r <= b) return tree[q][node];

		int mid = (l+r)>>1;

		pii p1 = query(2*node, l, mid, a, b, q);
		pii p2 = query(2*node+1, mid+1, r, a, b, q);

		if (q == 0) return max(p1, p2);
		return min(p1, p2);
	}
} seg;

int lca_range(int l, int r)
{
	int v_mx = seg.query(1, 1, n, l, r, 0).ss;
	int v_mn = seg.query(1, 1, n, l, r, 1).ss;

	return LCA.lca(v_mx, v_mn);
}

void upd(int &ans, int &fora, int l, int r, int i)
{
	if (i == l)
	{
		if (nivel[lca_range(l+1, r)] > nivel[ans])
			ans = lca_range(l+1, r), fora = i;
	}
	else if (i == r)
	{
		if (nivel[lca_range(l, r-1)] > nivel[ans])
			ans = lca_range(l, r-1), fora = i;
	}
	else
	{
		if (nivel[LCA.lca(lca_range(l, i-1), lca_range(i+1, r))] > nivel[ans])
			ans = LCA.lca(lca_range(l, i-1), lca_range(i+1, r)), fora = i;
	}
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 2; i <= n; i++)
	{
		int u;
		scanf("%d", &u);

		grafo[i].push_back(u);
		grafo[u].push_back(i);
	}

	LCA.dfs(1, 0); LCA.build(n);
	seg.build(1, 1, n);

	while (q--)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		int v_mx = seg.query(1, 1, n, l, r, 0).ss;
		int v_mn = seg.query(1, 1, n, l, r, 1).ss;

		int ans = 1, fora = v_mx;

		upd(ans, fora, l, r, v_mx);
		upd(ans, fora, l, r, v_mn);

		printf("%d %d\n", fora, nivel[ans]);
	}
}
