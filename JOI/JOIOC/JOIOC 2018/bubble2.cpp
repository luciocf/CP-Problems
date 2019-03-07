// JOI Open Contest 2018 - Bubble Sort 2
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "bubblesort2.h"

using namespace std;

const int maxn = 1e6+10;

int n;

int num[maxn], soma[maxn];

int tree[4*maxn], lazy[4*maxn];

set<int> Pos[maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = -soma[l]-(*Pos[l].begin());
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node] += lazy[node];

	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
{
	if (l > r) return;

	flush(node, l, r);
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node] += v;
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
	if (l > b || r < a) return -1e9-10;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V)
{
	n = A.size();

	unordered_map<int, int> Mp;
        vector<int> C;

	for (int i = 0; i < n; i++) C.push_back(A[i]);
	for (int i = 0; i < V.size(); i++) C.push_back(V[i]);

	sort(C.begin(), C.end());
	C.erase(unique(C.begin(), C.end()), C.end());

	int ind = 0;
	for (auto x: C)
		Mp[x] = ++ind, Pos[ind].insert(1e9+10);

	for (int i = 0; i < n; i++)
	{
		num[i] = Mp[A[i]];

		soma[num[i]]++;
		Pos[num[i]].insert(-i);
	}

	for (int i = 1; i <= ind; i++)
		soma[i] += soma[i-1];

	build(1, 1, ind);

	vector<int> ans(V.size());

	for (int i = 0; i < V.size(); i++)
	{
		int pos = X[i], v = Mp[V[i]];

		upd(1, 1, ind, num[pos], ind, 1);

		bool last = 0;

		if (pos == -(*Pos[num[pos]].begin())) last = 1;

		Pos[num[pos]].erase(-pos);

		if (last) upd(1, 1, ind, num[pos], num[pos], -(*Pos[num[pos]].begin())-pos);

		num[pos] = v;

		if (pos > -(*Pos[v].begin())) upd(1, 1, ind, v, v, *Pos[v].begin()+pos);

		Pos[v].insert(-pos);

		upd(1, 1, ind, v, ind, -1);

		ans[i] = 1+query(1, 1, ind, 1, ind);
	}

	return ans;
}
