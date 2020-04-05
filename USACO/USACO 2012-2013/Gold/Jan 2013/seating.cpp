// USACO 2012/2013 - Seating
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

struct Node
{
	int mn, mx;
} tree[4*maxn];

int n;
int lazy[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = {n, n};
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = {n, n};
}

void flush(int node, int l, int r)
{
	if (lazy[node] == -1) return;

	if (l != r)
		lazy[2*node] = lazy[2*node+1] = lazy[node];

	tree[node] = {lazy[node], lazy[node]};
	lazy[node] = -1;
}

void upd(int node, int l, int r, int a, int b, int t)
{
	if (l > r) return;
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] = t;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, t); upd(2*node+1, mid+1, r, a, b, t);

	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
	tree[node].mx = max(tree[2*node].mx, tree[2*node+1].mx);
}

int findL(int node, int l, int r, int p)
{
	flush(node, l, r);
	if (l > p || tree[node].mn > 0) return 0;

	if (l == r) return l;

	int mid = (l+r)>>1;

	int p1 = findL(2*node+1, mid+1, r, p);

	return (p1 == 0 ? findL(2*node, l, mid, p) : p1);
}

int findR(int node, int l, int r, int p)
{
	flush(node, l, r);
	if (r < p || tree[node].mn > 0) return n+1;

	if (l == r) return l;

	int mid = (l+r)>>1;

	int p1 = findR(2*node, l, mid, p);

	return (p1 == n+1 ? findR(2*node+1, mid+1, r, p) : p1);
}

int query(int node, int l, int r, int p)
{
	flush(node, l, r);
	if (l == r)
	{
		if (tree[node].mx < p) return -1;
		return l;
	}

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[2*node].mx >= p) return query(2*node, l, mid, p);
	return query(2*node+1, mid+1, r, p);
}

int main(void)
{
	freopen("seating.in", "r", stdin); freopen("seating.out", "w", stdout);

	int m;
	scanf("%d %d", &n, &m);

	memset(lazy, -1, sizeof lazy);
	build(1, 1, n);

	int ans = 0;

	while (m--)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'A')
		{
			int p;
			scanf("%d", &p);

			int pos = query(1, 1, n, p);

			if (pos == -1) ans++;
			else
			{
				int l = findL(1, 1, n, pos-1)+1;
				int r = findR(1, 1, n, pos+p)-1;

				upd(1, 1, n, pos, pos+p-1, 0);
				upd(1, 1, n, l, pos-1, pos-l);
				upd(1, 1, n, pos+p, r, r-pos-p+1);
			}
		}
		else
		{
			int a, b;
			scanf("%d %d", &a, &b);

			int l = findL(1, 1, n, a-1)+1, r = findR(1, 1, n, b+1)-1;

			upd(1, 1, n, l, r, r-l+1);
		}
	}

	printf("%d\n", ans);
}
