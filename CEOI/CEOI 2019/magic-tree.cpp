// CEOI 2019 - Magic Tree
// Lúcio Cardoso

// Solution is the same as in editorial: https://codeforces.com/blog/entry/68748

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

// lazy1 -> set
// lazy2 -> sum
struct Node
{
	ll mx, lazy1, lazy2;
	Node *l, *r;

	Node()
	{
		mx = lazy1 = lazy2 = 0;
		l = r = NULL;
	}
} *tree[maxn];

int n, m, k;

int d[maxn], w[maxn];

vector<int> grafo[maxn];
set<int> st[maxn];

void flush(Node *node, int l, int r)
{
	if (!node->l) node->l = new Node();
	if (!node->r) node->r = new Node();

	if (!node->lazy1 && !node->lazy2) return;

	if (l != r)
	{
		if (node->lazy1)
		{
			node->l->lazy1 = node->r->lazy1 = node->lazy1;
			node->l->lazy2 = node->r->lazy2 = 0;
		}
		else
		{
			if (node->l->lazy1) node->l->lazy1 += node->lazy2;
			else node->l->lazy2 += node->lazy2;

			if (node->r->lazy1) node->r->lazy1 += node->lazy2;
			else node->r->lazy2 += node->lazy2;
		}
	}

	if (node->lazy1) node->mx = node->lazy1;
	else node->mx += node->lazy2;

	node->lazy1 = node->lazy2 = 0;
}

void upd(Node *node, int l, int r, int a, int b, ll v, int type)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		if (type == 1)
		{
			node->lazy1 = v;
			node->lazy2 = 0;
		}
		else
		{
			if (node->lazy1) node->lazy1 += v;
			else node->lazy2 += v;
		}

		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(node->l, l, mid, a, b, v, type);
	upd(node->r, mid+1, r, a, b, v, type);

	node->mx = max(node->l->mx, node->r->mx);
}

ll query(Node *node, int l, int r, int a, int b)
{
	flush(node, l, r);

	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return node->mx;

	int mid = (l+r)>>1;

	return max(query(node->l, l, mid, a, b), query(node->r, mid+1, r, a, b));
}

int busca(Node *node, int l, int r, ll v)
{
	flush(node, l, r);

	if (l == r)
	{
		if (node->mx > v) return l;
		return k+1;
	}

	int mid = (l+r)>>1;

	flush(node->l, l, mid); flush(node->r, mid+1, r);

	if (node->l->mx > v) return busca(node->l, l, mid, v);
	return busca(node->r, mid+1, r, v);
}

void merge(int u, int v)
{
	bool rev = 0;
	if (st[u].size() < st[v].size()) swap(u, v), rev = 1;

	for (auto it = st[v].begin(); it != st[v].end(); ++it)
	{
		int x = *it, lim = k;

		if (next(it) != st[v].end()) lim = *next(it)-1;

		if (lim >= x) upd(tree[u], 1, k, x, lim, query(tree[v], 1, k, x, x), 2);

		st[u].insert(x);
	}

	if (rev)
	{
		swap(st[u], st[v]);
		swap(tree[u], tree[v]);
	}
}

void solve(int u, int p)
{
	tree[u] = new Node();

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		solve(v, u);
		merge(u, v);
	}

	if (d[u])
	{
		ll x = 1ll*w[u] + 1ll*query(tree[u], 1, k, d[u], d[u]);

		int pos = busca(tree[u], 1, k, x);

		if (pos > d[u])
		{
			upd(tree[u], 1, k, d[u], pos-1, x, 1);

			st[u].insert(d[u]);
		}
	}
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		grafo[i].push_back(p);
		grafo[p].push_back(i);
	}

	for (int i = 1; i <= m; i++)
	{
		int v;
		scanf("%d", &v);
		scanf("%d %d", &d[v], &w[v]);
	}

	solve(1, 0);

	printf("%lld\n", query(tree[1], 1, k, 1, k));
}
