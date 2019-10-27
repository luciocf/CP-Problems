// BOI 2011 - Growing Trees
// Lúcio Cardoso

// Same idea as CS Academy - Candles

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int a[maxn];

int tree[2][4*maxn], lazy[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[0][node] = tree[1][node] = a[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[0][node] = min(tree[0][2*node], tree[0][2*node+1]);
	tree[1][node] = max(tree[1][2*node], tree[1][2*node+1]); 
}

void flush(int node, int l, int r)
{
	if (!lazy[node] || l > r) return;

	if (l != r)
		lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

	tree[0][node] += lazy[node];
	tree[1][node] += lazy[node];
	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	flush(node, l, r);
	if (l > b || r < a || a > b) return;

	if (l >= a && r <= b)
	{
		lazy[node] = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[0][node] = min(tree[0][2*node], tree[0][2*node+1]);
	tree[1][node] = max(tree[1][2*node], tree[1][2*node+1]); 
}

int findVal(int node, int l, int r, int pos)
{
	flush(node, l, r);
	if (l == r) return tree[0][node];

	int mid = (l+r)>>1;

	if (pos <= mid) return findVal(2*node, l, mid, pos);
	return findVal(2*node+1, mid+1, r, pos);
}

int findL(int node, int l, int r, int v)
{
	flush(node, l, r);
	if (l == r)
	{
		if (tree[0][node] >= v) return l;
		return n+1;
	}

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[1][2*node] < v) return findL(2*node+1, mid+1, r, v);
	return findL(2*node, l, mid, v);
}

int findR(int node, int l, int r, int v)
{
	flush(node, l, r);
	if (l == r)
	{
		if (tree[0][node] <= v) return l;
		return -1;
	}

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[0][2*node+1] > v) return findR(2*node, l, mid, v);
	return findR(2*node+1, mid+1, r, v);
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	build(1, 1, n);

	for (int i = 1; i <= q; i++)
	{
		char op;
		int a, b;

		scanf(" %c %d %d", &op, &a, &b);

		if (op == 'F')
		{
			int l = findL(1, 1, n, b), r = min(n, l+a-1);

			if (l == n+1) continue;

			int val = findVal(1, 1, n, r);
			int l_val = findL(1, 1, n, val), r_val = findR(1, 1, n, val);

			assert(l_val <= r_val);

			upd(1, 1, n, l, l_val-1, 1);

			int resto = a-(l_val-l);
			upd(1, 1, n, max(l_val, r_val-resto+1), r_val, 1);
		}
		else
		{
			int l = findL(1, 1, n, a);
			int r = findR(1, 1, n, b);

			if (l > r) printf("0\n");
			else printf("%d\n", r-l+1);
		}
	}
}
