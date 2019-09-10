// IOI 2005 - Mountains
// Lúcio Cardoso

// Use an implicit segment tree with lazy propagation, keeping the maximum
// "prefix sum" in a node and the whole sum. This way, we can find the answer to the query
// with a traversal in the segment tree.

#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9+10;

struct Node
{
	Node *l, *r;

	int soma, mx;
	int lazy;

	Node()
	{
		l = r = NULL;
		soma = mx = 0;
		lazy = inf;
	}
};

int get_s(Node *node)
{
	if (node) return node->soma;
	return 0;
}

int get_mx(Node *node)
{
	if (node) return node->mx;
	return 0;
}

void flush(Node *node, int l, int r)
{
	if (node->lazy == inf) return;

	int mid = (l+r)>>1;

	if (l != r)
	{
		if (!node->l) node->l = new Node;
		if (!node->r) node->r = new Node;

		node->l->lazy = node->r->lazy = node->lazy;

		node->l->soma = (mid-l+1)*node->l->lazy;
		node->l->mx = (node->l->soma > 0 ? node->l->soma : 0);

		node->r->soma = (r-mid)*node->r->lazy;
		node->r->mx = (node->r->soma > 0 ? node->r->soma : 0);
	}

	node->soma = (r-l+1)*node->lazy;
	node->mx = (node->soma > 0 ? node->soma : 0);

	node->lazy = inf;
}

void upd(Node *node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);

	if (l == a && r == b)
	{
		node->lazy = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	if (b <= mid)
	{
		if (!node->l) node->l = new Node;
		upd(node->l, l, mid, a, b, v);
	}
	else if (a > mid)
	{
		if (!node->r) node->r = new Node;
		upd(node->r, mid+1, r, a, b, v);
	}
	else
	{
		if (!node->l) node->l = new Node;
		if (!node->r) node->r = new Node;

		upd(node->l, l, mid, a, mid, v);
		upd(node->r, mid+1, r, mid+1, b, v);
	}

	node->soma = get_s(node->l) + get_s(node->r);
	node->mx = max(get_mx(node->l), get_s(node->l) + get_mx(node->r));
}

int query(Node *node, int l, int r, int k)
{
	flush(node, l, r);

	if (l == r) return l-1;

	int mid = (l+r)>>1;

	if (!node->l) node->l = new Node;

	if (node->l->mx > k) return query(node->l, l, mid, k);

	if (!node->r) node->r = new Node;
	return query(node->r, mid+1, r, k-node->l->soma);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	Node *node = new Node;

	while (true)
	{
		char c;
		scanf(" %c", &c);

		if (c == 'E') break;

		if (c == 'I')
		{
			int l, r, v;
			scanf("%d %d %d", &l, &r, &v);

			upd(node, 1, n, l, r, v);
		}
		else
		{
			int k;
			scanf("%d", &k);

			flush(node, 1, n);

			if (k >= node->mx)
				printf("%d\n", n);
			else
				printf("%d\n", query(node, 1, n, k));
		}
	}
}
