// Codeforces 438D - The Child and Sequence
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

struct Node
{
	int mn, mx, lazy;
	ll soma;
} tree[4*maxn];

int a[maxn];

void merge(int node)
{
	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
	tree[node].mx = max(tree[2*node].mx, tree[2*node+1].mx);
	tree[node].soma = tree[2*node].soma + tree[2*node+1].soma;
}

void build(int node, int l, int r)
{
	tree[node].lazy = -1;
	if (l == r)
	{
		tree[node].mn = tree[node].mx = tree[node].soma = a[l];
		tree[node].lazy = -1;
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	merge(node);
}

void flush(int node, int l, int r)
{
	if (tree[node].lazy == -1) return;

	if (l != r)
		tree[2*node].lazy = tree[2*node+1].lazy = tree[node].lazy;

	tree[node].mn = tree[node].mx = tree[node].lazy;
	tree[node].soma = 1ll*(r-l+1)*tree[node].lazy;

	tree[node].lazy = -1;
}

void upd1(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a || tree[node].mx < v) return;

	if (l >= a && r <= b && tree[node].mn == tree[node].mx)
	{
		tree[node].lazy = tree[node].mn%v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd1(2*node, l, mid, a, b, v); upd1(2*node+1, mid+1, r, a, b, v);

	merge(node);
}

void upd2(int node, int l, int r, int a, int b, int v)
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

	upd2(2*node, l, mid, a, b, v); upd2(2*node+1, mid+1, r, a, b, v);

	merge(node);
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node].soma;

	int mid = (l+r)>>1;

	return (query(2*node, l, mid, a, b)+query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	build(1, 1, n);

	for (int i = 1; i <= m; i++)
	{
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);

		if (op == 1)
		{			
			printf("%lld\n", query(1, 1, n, l, r));
		}
		else if (op == 2)
		{
			int v;
			scanf("%d", &v);

			upd1(1, 1, n, l, r, v);
		}
		else
		{
			upd2(1, 1, n, l, l, r);
		}

	}
}
