// USACO Platinum Dec 2015 - Counting Haybales
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const long long inf = 2e18+10;

int a[maxn];

typedef long long ll;

struct Node
{
	ll mn, val;
} tree[4*maxn];

ll lazy[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].mn = tree[node].val = a[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
	tree[node].val = tree[2*node].val + tree[2*node+1].val; 
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node].mn += lazy[node];
	tree[node].val += 1ll*(r-l+1)*lazy[node];

	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
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

	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
	tree[node].val = tree[2*node].val + tree[2*node+1].val; 
}

ll query(int node, int l, int r, int a, int b, bool op)
{
	flush(node, l, r);
	if (l > b || r < a) return (op == 0 ? inf : 0);
	if (l >= a && r <= b) return (op == 0 ? tree[node].mn : tree[node].val);

	int mid = (l+r)>>1;

	if (!op) return min(query(2*node, l, mid, a, b, op), query(2*node+1, mid+1, r, a, b, op));
	return query(2*node, l, mid, a, b, op)+query(2*node+1, mid+1, r, a, b, op);
}

int main(void)
{
	FILE *fin = fopen("haybales.in", "r");
	FILE *fout = fopen("haybales.out", "w");

	int n, q;
	fscanf(fin, "%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &a[i]);

	build(1, 1, n);

	while (q--)
	{
		char op;
		fscanf(fin, " %c", &op);

		if (op == 'M')
		{
			int l, r;
			fscanf(fin, "%d %d", &l, &r);

			fprintf(fout, "%lld\n", query(1, 1, n, l, r, 0));
		}
		else if (op == 'P')
		{
			int l, r, v;
			fscanf(fin, "%d %d %d", &l, &r, &v);

			upd(1, 1, n, l, r, v);
		}
		else
		{
			int l, r;
			fscanf(fin, "%d %d", &l, &r);

			fprintf(fout, "%lld\n", query(1, 1, n, l, r, 1));
		}
	}
}
