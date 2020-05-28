// IOI 2014 - Wall
// Lúcio Cardoso

// Solution is the same as: https://github.com/luciocf/Problems/blob/master/Codeforces/444C.cpp

// Basically, only execute lazy updates in nodes of the segment tree that are inside the interval AND such that every leaf
// in this interval has the same height

#include <bits/stdc++.h>
#include "wall.h"

using namespace std;

const int maxn = 2e6+10;

struct Node
{
	int mx, mn;
	int lazy;

	Node()
	{
		mx = mn = 0;
		lazy = -1;
	}
} tree[4*maxn];

void flush(int node, int l, int r)
{
	if (tree[node].lazy == -1) return;

	if (l != r)
		tree[2*node].lazy = tree[2*node+1].lazy = tree[node].lazy;

	tree[node].mn = tree[node].mx = tree[node].lazy;

	tree[node].lazy = -1;
}

void upd(int node, int l, int r, int a, int b, int h, int op)
{
	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b && tree[node].mn == tree[node].mx)
	{
		if (op == 1 && tree[node].mn >= h) return;
		if (op == 2 && tree[node].mn <= h) return;

		tree[node].lazy = h;

		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, h, op); upd(2*node+1, mid+1, r, a, b, h, op);

	tree[node].mx = max(tree[2*node].mx, tree[2*node+1].mx);
	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
}

int query(int node, int l, int r, int pos)
{
	flush(node, l, r);
	if (l == r) return tree[node].mn;

	int mid = (l+r)>>1;

	if (pos <= mid) return query(2*node, l, mid, pos);
	return query(2*node+1, mid+1, r, pos);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[])
{
	for (int i = 0; i < k; i++)
		upd(1, 1, n, left[i]+1, right[i]+1, height[i], op[i]);

	for (int i = 1; i <= n; i++)
		finalHeight[i-1] = query(1, 1, n, i);
}

