// Infoarena - Curent
// Lúcio Cardoso

// Solution:

// Notice a vertex is only on if none of its ancestors are off. Let's linearize the tree.
// The problem now becomes handling these 2 queries:

//	1. Add +1 or -1 in a range (vertex becomes off or on, respectively)
//	2. Count the amount of zeroes in a range (if a vertex has value 0, none of its ancestors are off)

// This can be solved with lazy propagation by storing 2 values in the segment tree: The minimum in a range and
// the amount of minimums in a range. See the code for further details.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100043;

struct Query
{
	int d, u, t;
} query[maxn];

struct Node
{
	int mn, qtd, lazy;
} tree[4*maxn];

int n, m, q;

int dia[maxn];

int st[maxn], en[maxn], tt;

vector<int> grafo[maxn];

bool comp(Query a, Query b) {return a.d < b.d;}

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	en[u] = tt;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = {0, 1, 0};
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = {0, r-l+1, 0};
}

void flush(int node, int l, int r)
{
	if (tree[node].lazy == 0) return;

	if (l != r)
		tree[2*node].lazy += tree[node].lazy, tree[2*node+1].lazy += tree[node].lazy;

	tree[node].mn += tree[node].lazy;
	tree[node].lazy = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		tree[node].lazy = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
	tree[node].qtd = 0;

	if (tree[2*node].mn == tree[node].mn) tree[node].qtd += tree[2*node].qtd;
	if (tree[2*node+1].mn == tree[node].mn) tree[node].qtd += tree[2*node+1].qtd;
}

int main(void)
{
	freopen("curent.in", "r", stdin); freopen("curent.out", "w", stdout);
	scanf("%d", &n);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		grafo[p].push_back(i);
	}

	dfs(1, 0); build(1, 1, n);

	scanf("%d", &m);

	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &query[i].d, &query[i].u, &query[i].t);

	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
		scanf("%d", &dia[i]);

	sort(query+1, query+m+1, comp);

	int ind = 1;
	for (int i = 1; i <= m+1; i++)
	{
		while (ind <= q && dia[ind] < query[i].d)
		{
			flush(1, 1, n);
			
			if (tree[1].mn == 0) printf("%d\n", tree[1].qtd);
			else printf("0\n");

			++ind;
		}

		int u = query[i].u, t = query[i].t;

		if (t == 0) upd(1, 1, n, st[u], en[u], 1);
		else upd(1, 1, n, st[u], en[u], -1);
	}

	while (ind <= q)
	{
		flush(1, 1, n);
		
		if (tree[1].mn == 0) printf("%d\n", tree[1].qtd);
			else printf("0\n");

		++ind;
	}
}
