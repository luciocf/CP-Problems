// COI Regional 2009 - Cvjetici
// Lúcio Cardoso

// Solution: http://hsin.hr/coci/archive/2008_2009/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int tree[4*maxn], lazy[4*maxn];

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node] += (r-l+1)*lazy[node];
	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	if (l > r) return;

	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] = v;
		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

	tree[node] = tree[2*node]+tree[2*node+1];
}

int query(int node, int l, int r, int pos)
{
	flush(node, l, r);
	if (l == r) return tree[node];

	int mid = (l+r)>>1;

	if (pos <= mid) return query(2*node, l, mid, pos);
	return query(2*node+1, mid+1, r, pos);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int m = maxn-10;

	for (int i = 1; i <= n; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		int a = query(1, 1, m, l), b = query(1, 1, m, r);

		printf("%d\n", a+b);

		upd(1, 1, m, l, l, -a); upd(1, 1, m, r, r, -b);
		upd(1, 1, m, l+1, r-1, 1);
	}
}
