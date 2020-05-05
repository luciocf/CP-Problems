// DMOJ - PIB '20 P6 - Rotational Top Trees
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;

struct Query
{
	int op, k, ind;
};

struct node
{
	ll v;
	int w, sz;
	node *l, *r;

	node(ll vv)
	{
		v = vv, w = rand(), sz = 1;
		l = r = NULL;
	}
};

typedef node*& node_t;

node *root;

int a[maxn];

ll soma[maxn];

ll ans[maxn];

vector<Query> query[maxn];

multiset<int> st[maxn];

vector<int> grafo[maxn];

int sz(node *t) {return (t ? t->sz : 0);}

void op(node *t)
{
	if (t) t->sz = sz(t->l)+sz(t->r)+1;
}

void split(node *t, node_t l, node_t r, ll v)
{
	if (!t) return void(l=r=NULL);

	if (t->v > v) split(t->l, l, t->l, v), r = t;
	else split(t->r, t->r, r, v), l = t;

	op(t);
}

void merge(node_t t, node *l, node *r)
{
	if (!l || !r) t = (l ? l : r);
	else if (l->w > r->w) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;

	op(t);
}

void insert(node_t t, ll v)
{
	node *aux = new node(v);
	node *t1 = NULL, *t2 = NULL;

	split(t, t1, t2, v);
	merge(t1, t1, aux);
	merge(t, t1, t2);

	op(t);
}

void erase(node_t t, ll v)
{
	if (t->v == v) merge(t, t->l, t->r);
	else if (t->v > v) erase(t->l, v);
	else erase(t->r, v);

	op(t);
}

ll kth(node *t, int k)
{
	if (sz(t->l) == k-1) return t->v;
	else if (sz(t->l) >= k) return kth(t->l, k);
	else return kth(t->r, k-sz(t->l)-1);
}

void dfs(int u, int p)
{
	soma[u] = a[u];
	st[u].insert(-a[u]);

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		soma[u] += soma[v];
		st[u].insert(*st[v].begin());
	}
}

void solve1(int u, int p)
{
	for (auto q: query[u])
	{
		int op = q.op, k = q.k, ind = q.ind;

		if (op == 1) ans[ind] = kth(root, k);
	}

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		ll old_u = soma[u], old_v = soma[v];

		erase(root, soma[u]); erase(root, soma[v]);

		soma[u] -= soma[v]; soma[v] += soma[u];

		insert(root, soma[u]); insert(root, soma[v]);

		solve1(v, u);

		erase(root, soma[u]); erase(root, soma[v]);

		soma[u] = old_u, soma[v] = old_v;

		insert(root, soma[u]); insert(root, soma[v]);
	}
}

void solve2(int u, int p)
{
	for (auto q: query[u])
	{
		int op = q.op, k = q.k, ind = q.ind;

		if (op == 2) ans[ind] = kth(root, k);
	}

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		int old_u = *st[u].begin(), old_v = *st[v].begin();

		erase(root, -old_u); erase(root, -old_v);

		st[u].erase(st[u].find(old_v)); st[v].insert(*st[u].begin());

		insert(root, -*st[u].begin()); insert(root, -*st[v].begin());

		solve2(v, u);

		erase(root, -*st[u].begin()); erase(root, -*st[v].begin());

		st[v].erase(st[v].find(*st[u].begin())); st[u].insert(old_v);

		insert(root, -*st[u].begin()); insert(root, -*st[v].begin());
	}
}

int main(void)
{
	int n, q;
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

	dfs(1, 0);

	for (int i = 1; i <= q; i++)
	{
		int op, r, k;
		scanf("%d %d %d", &op, &r, &k);

		query[r].push_back({op, n-k+1, i});
	}

	root = NULL;
	for (int i = 1; i <= n; i++)
		insert(root, soma[i]);

	solve1(1, 0);

	root = NULL;
	for (int i = 1; i <= n; i++)
		insert(root, -*st[i].begin());

	solve2(1, 0);

	for (int i = 1; i <= q; i++)
		printf("%lld\n", ans[i]);
}
