// Codeforces 916E - Jamie and Tree
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n;
int a[maxn];

int nivel[maxn], in[maxn], out[maxn], tt;

vector<int> grafo[maxn];

struct BinaryLifting
{
	int tab[maxn][20];

	void dfs(int u, int p)
	{
		in[u] = ++tt;

		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u;
			dfs(v, u);
		}

		out[u] = tt;
	}

	void build(void)
	{
		for (int j = 1; j < 20; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int intersect(int u, int v, int w_u, int w_v)
	{
		if (nivel[u] < nivel[v]) swap(u, v), swap(w_u, w_v);

		for (int i = 19; i >= 0; i--)
			if (nivel[u]-(1<<i) >= nivel[v] && w_u >= (1<<i))
				u = tab[u][i], w_u -= (1<<i);

		if (nivel[u] != nivel[v]) return -1;
		if (u == v) return u;

		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i] && min(w_u, w_v) >= (1<<i))
				u = tab[u][i], v = tab[v][i], w_u -= (1<<i), w_v -= (1<<i);

		if (tab[u][0] != tab[v][0] || min(w_u, w_v) == 0) return -1;
		return tab[u][0];
	}

	int dist(int u, int v)
	{
		return nivel[u] + nivel[v] - 2*nivel[intersect(u, v, nivel[u], nivel[v])];
	}

	int get_intersection(int u, int v, int root)
	{
		int k = -1;
		int lca_u = intersect(u, root, nivel[u], nivel[root]);
		int lca_v = intersect(v, root, nivel[v], nivel[root]);

		int aux = intersect(u, v, nivel[u]-nivel[lca_u], nivel[v]-nivel[lca_v]);
		if (k == -1 || (aux != -1 && dist(aux, root) > dist(k, root))) k = aux;

		aux = intersect(u, root, nivel[u]-nivel[lca_u], nivel[root]-nivel[lca_v]);
		if (k == -1 || (aux != -1 && dist(aux, root) > dist(k, root))) k = aux;

		aux = intersect(root, v, nivel[root]-nivel[lca_u], nivel[v]-nivel[lca_v]);
		if (k == -1 || (aux != -1 && dist(aux, root) > dist(k, root))) k = aux;

		aux = intersect(root, root, nivel[root]-nivel[lca_u], nivel[root]-nivel[lca_v]);
		if (k == -1 || (aux != -1 && dist(aux, root) > dist(k, root))) k = aux;

		return k;
	}

	int kth(int u, int k)
	{
		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && k >= (1<<i))
				u = tab[u][i], k -= (1<<i);

		return u;
	}
} LCA;

struct SegmentTree
{
	ll tree[3*maxn], lazy[3*maxn];

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}

		tree[node] += 1ll*(r-l+1)*lazy[node];
		lazy[node] = 0;
	}

	void upd(int node, int l, int r, int a, int b, int v)
	{
		flush(node, l, r);
		if (l > b || r < a) return;

		if (l >= a && r <= b)
		{
			lazy[node] = 1ll*v;
			flush(node, l, r);
			return;
		}

		int mid = (l+r)>>1;

		upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

		tree[node] = tree[2*node] + tree[2*node+1];
	}

	ll query(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[node];

		int mid = (l+r)>>1;

		return query(2*node, l, mid, a, b) + query(2*node+1, mid+1, r, a, b);
	}
} seg;

bool is_ancestor(int u, int v)
{
	return (in[v] >= in[u] && out[v] <= out[u]);
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	LCA.dfs(1, 0); LCA.build();

	for (int i = 1; i <= n; i++)
		seg.upd(1, 1, n, in[i], in[i], a[i]);

	int root = 1;

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int v;
			scanf("%d", &v);

			root = v;
		}
		else if (op == 2)
		{
			int u, v, x;
			scanf("%d %d %d", &u, &v, &x);

			int k = LCA.get_intersection(u, v, root);

			if (!is_ancestor(k, root)) seg.upd(1, 1, n, in[k], out[k], x);
			else
			{
				seg.upd(1, 1, n, 1, n, x);

				if (k != root)
				{
					int w = LCA.kth(root, nivel[root]-nivel[k]-1);
					seg.upd(1, 1, n, in[w], out[w], -x);
				}
			}
		}
		else
		{
			int u;
			scanf("%d", &u);

			if (!is_ancestor(u, root)) printf("%lld\n", seg.query(1, 1, n, in[u], out[u]));
			else
			{
				if (u == root) printf("%lld\n", seg.query(1, 1, n, 1, n));
				else
				{
					int w = LCA.kth(root, nivel[root]-nivel[u]-1);

					printf("%lld\n", seg.query(1, 1, n, 1, n) - seg.query(1, 1, n, in[w], out[w]));
				}
			}
		}
	}
}
