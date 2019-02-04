// Seletiva IOI 2017 - Árvore
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

const int maxl = 20;

struct Node
{
	Node *l, *r;
	int v;

	Node()
	{
		l = r = NULL;
		v = 0;
	}
};

Node *version[maxn];

int num[maxn], ind[maxn], n, V;

int tab[maxn][maxl], pai[maxn], nivel[maxn];

map<int, int> back;

vector<int> grafo[maxn];

void compress(void)
{
	int aux = 0;
	map<int, int> M;
	vector<int> v;

	for (int i = 1; i <= n; i++)
		v.push_back(num[i]);

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++)
		if (M.find(v[i]) == M.end())
			M[v[i]] = ++aux, back[aux] = v[i];

	for (int i = 1; i <= n; i++)
		num[i] = M[num[i]];
}

void build(Node *node, int l, int r)
{
	if (l == r) return;

	int mid = (l+r)>>1;

	node->l = new Node(), node->r = new Node();

	build(node->l, l, mid); build(node->r, mid+1, r);
}

void upd(Node *prev, Node *node, int l, int r, int pos)
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
		if (node->l == NULL) node->l = new Node();

		upd(prev->l, node->l, l, mid, pos);
	}
	else
	{
		node->l = prev->l;
		if (node->r == NULL) node->r = new Node();

		upd(prev->r, node->r, mid+1, r, pos);
	}

	node->v = node->l->v+node->r->v;
}

int kth(Node *node1, Node *node2, Node *node3, int l, int r, int k, int num_lca)
{
	if (l == r) return l;

	int mid = (l+r)>>1;
	int x = node1->l->v+node2->l->v-2*node3->l->v;

	if (num_lca >= l && num_lca <= mid) x--;

	if (x >= k) return kth(node1->l, node2->l, node3->l, l, mid, k, num_lca);
	return kth(node1->r, node2->r, node3->r, mid+1, r, k-x, num_lca);
}

void dfs(int u, int p)
{
	ind[u] = ++V;
	version[ind[u]] = new Node();

	upd(version[ind[p]], version[ind[u]], 1, n, num[u]);

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pai[v] = u, nivel[v] = nivel[u]+1;

		dfs(v, u);
	}
}

void build_lca(void)
{
	memset(tab, -1, sizeof tab);

	for (int i = 1; i <= n; i++)
		tab[i][0] = pai[i];

	for (int j = 1; j < maxl; j++)
		for (int i = 1; i <= n; i++)
			if (tab[i][j-1] != -1)
				tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = maxl-1; i >= 0; i--)
		if (tab[u][i] != -1 && tab[v][i] != -1 && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return pai[u];
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> num[i];

	for (int i = 1; i <= n-1; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	compress();

	version[0] = new Node();
	build(version[0], 1, n);

	dfs(1, 0);
	build_lca();

	for (int i = 1; i <= m; i++)
	{
		int u, v, k;
		cin >> k >> u >> v;

		int low = lca(u, v);
		cout << back[kth(version[ind[u]], version[ind[v]], version[ind[pai[low]]], 1, n, k, num[low])] << "\n";
	}
}
