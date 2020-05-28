// Codeforces 444C - DZY Loves Colors
// Lúcio Cardoso

// Solution:

// Use two segment trees with lazy updates: One to deal with setting an interval with a color c, and one
// to add a value of colourfulness to an interval.

// To deal with this second update, instead of updating the nodes in the segment tree that are inside the interval,
// update the nodes (l, r) in the segment tree that are inside the interval AND such that every index in [l, r] has the same color.
// To check if an interval in monochromatic, store the minimum and maximum color in every node of the segment tree, then check if 
// the minimum colour in a node is equal to the maximum one.

// The complexity is O(n log n) amortized

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

struct Node
{
	int mx, mn;
	ll soma, lazy1, lazy2;
} tree[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].mx = tree[node].mn = l;
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node].mx = max(tree[2*node].mx, tree[2*node+1].mx);
	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
}

void flush(int node, int l, int r)
{
	if (!tree[node].lazy1 && !tree[node].lazy2) return;

	if (l != r)
	{
		tree[2*node].lazy1 = tree[2*node+1].lazy1 = tree[node].lazy1;
		tree[2*node].lazy2 += tree[node].lazy2, tree[2*node+1].lazy2 += tree[node].lazy2;
	}

	tree[node].mn = tree[node].mx = tree[node].lazy1;
	tree[node].soma += 1ll*(r-l+1)*tree[node].lazy2;

	tree[node].lazy1 = tree[node].lazy2 = 0;
}

void upd(int node, int l, int r, int a, int b, int c)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b && tree[node].mn == tree[node].mx)
	{
		tree[node].lazy1 = c;
		tree[node].lazy2 = abs(tree[node].mn-c);

		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, c); upd(2*node+1, mid+1, r, a, b, c);

	tree[node].mx = max(tree[2*node].mx, tree[2*node+1].mx);
	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
	tree[node].soma = tree[2*node].soma + tree[2*node+1].soma;
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node].soma;

	int mid = (l+r)>>1;

	return (query(2*node, l, mid, a, b) + query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	build(1, 1, n);

	while (m--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);

			upd(1, 1, n, l, r, x);
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			printf("%lld\n", query(1, 1, n, l, r));
		}
	}
}
