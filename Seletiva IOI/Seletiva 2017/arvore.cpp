// Seletiva IOI 2017 - Árvore
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

struct Node
{
	int v;
	Node *l, *r;

	Node()
	{
		v = 0;
		l = r = NULL;
	}
};

int n, q;
int a[maxn];

int nivel[maxn], tab[maxn][21];

vector<int> grafo[maxn];

Node *version[maxn];

void build(Node *node, int l, int r)
{
	if (l == r) return;

	int mid = (l+r)>>1;

	node->l = new Node(), node->r = new Node();

	build(node->l, l, mid); build(node->r, mid+1, r);
}

void upd(Node *prev, Node *node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		node->v = prev->v+1;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid)
	{
		node->r = prev->r;
		if (!node->l) node->l = new Node();

		upd(prev->l, node->l, l, mid, pos, v);
	}
	else
	{
		node->l = prev->l;
		if (!node->r) node->r = new Node();

		upd(prev->r, node->r, mid+1, r, pos, v);
	}

	node->v = node->l->v+node->r->v;
}

int kth(Node *node1, Node *node2, Node *node3, int l, int r, int k, int num)
{
	if (l == r) return l;

	int mid = (l+r)>>1;

	int qtd = node1->l->v + node2->l->v - 2*node3->l->v + (num >= l && num <= mid);

	if (qtd >= k) return kth(node1->l, node2->l, node3->l, l, mid, k, num);
	return kth(node1->r, node2->r, node3->r, mid+1, r, k-qtd, num);
}

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, tab[v][0] = u;
		dfs(v, u);
	}
}

void build_tab(void)
{
	for (int j = 1; j < 21; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = 20; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = 20; i >= 0; i--)
		if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return tab[u][0];
}

void dfs2(int u, int p)
{
	version[u] = new Node();
	upd(version[p], version[u], 1, maxn-1, a[u], 1);

	for (auto v: grafo[u])
		if (v != p)
			dfs2(v, u);
}

int main(void)
{
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	version[0] = new Node();
	build(version[0], 1, maxn-1);

	dfs(1, 0);
	dfs2(1, 0);
	build_tab();

	for (int i = 1; i <= q; i++)
	{
		int u, v, k;
		scanf("%d %d %d", &k, &u, &v);

		int l = lca(u, v);

		printf("%d\n", kth(version[u], version[v], version[l], 1, maxn-1, k, a[l]));
	}
}
