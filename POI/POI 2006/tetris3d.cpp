// POI 2006 - Tetris 3D
// Lúcio Cardoso

// Solution is the same as: https://github.com/nikolapesic2802/Programming-Practice/blob/master/tetris%203d/main.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

struct SegTree
{
	int tree[2050], lazy[2050];

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r)
		{
			lazy[2*node] = max(lazy[2*node], lazy[node]);
			lazy[2*node+1] = max(lazy[2*node+1], lazy[node]);
		}

		tree[node] = max(tree[node], lazy[node]);
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

		tree[node] = max(tree[2*node], tree[2*node+1]);
	}

	int query(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[node];

		int mid = (l+r)>>1;

		return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
	}
};

struct SegTree2D
{
	SegTree tree[2050], full[2050];

	void upd(int node, int l, int r, int a1, int b1, int a2, int b2, int v)
	{
		if (l > b1 || r < a1) return;

		tree[node].upd(1, 1, maxn-1, a2, b2, v);

		if (l >= a1 && r <= b1)
		{
			full[node].upd(1, 1, maxn-1, a2, b2, v);
			return;
		}

		int mid = (l+r)>>1;

		upd(2*node, l, mid, a1, b1, a2, b2, v); upd(2*node+1, mid+1, r, a1, b1, a2, b2, v);
	}

	int query(int node, int l, int r, int a1, int b1, int a2, int b2)
	{
		if (l > b1 || r < a1) return 0;
		if (l >= a1 && r <= b1) return tree[node].query(1, 1, maxn-1, a2, b2);

		int mid = (l+r)>>1;

		int val = full[node].query(1, 1, maxn-1, a2, b2);

		return max({query(2*node, l, mid, a1, b1, a2, b2), query(2*node+1, mid+1, r, a1, b1, a2, b2), val});
	}
} seg;

int main(void)
{
	int d, s, n;
	scanf("%d %d %d", &d, &s, &n);

	while (n--)
	{
		int a, b, w, x, y;
		scanf("%d %d %d %d %d", &a, &b, &w, &x, &y);

		x++, y++;

		int mx = seg.query(1, 1, maxn-1, x, x+a-1, y, y+b-1);
		seg.upd(1, 1, maxn-1, x, x+a-1, y, y+b-1, mx+w);
	}

	printf("%d\n", seg.query(1, 1, maxn-1, 1, d, 1, s));
}
