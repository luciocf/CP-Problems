// IZhO 2019 - Hedgehog Daniyar and Algorithms
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;

typedef long long ll;
 
const int maxn = 1e6+10;
const int inf = 1e9+10;
 
int n;
int a[maxn];

int ans[maxn];

struct Query
{
	int l, r, k;
	int ind;
} qry[maxn];
 
struct SegmentTree
{
	ll tree[4*maxn];
	ll lazy[4*maxn];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node] = a[l];
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
			lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

		tree[node] += lazy[node];
		lazy[node] = 0;
	}

	void upd(int node, int l, int r, int a, int b, int v)
	{
		flush(node, l, r);
		if (l > r || l > b || r < a) return;
		if (l >= a && r <= b)
		{
			lazy[node] = 1ll*v;
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
} seg;

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
 
	seg.build(1, 1, n);
 
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &qry[i].l, &qry[i].r, &qry[i].k);
		qry[i].ind = i;
	}

	sort(qry+1, qry+m+1, [&] (Query a, Query b) {return a.l > b.l;});

	int ptr = n+1;
	stack<int> stk;

	for (int i = 1; i <= m; i++)
	{
		int l = qry[i].l, r = qry[i].r, k = qry[i].k;

		while (ptr > l)
		{
			ptr--;
			seg.upd(1, 1, n, ptr, ptr, -a[ptr]);

			while (stk.size() && a[ptr] > a[stk.top()])
			{
				int ind = stk.top(); stk.pop();

				seg.upd(1, 1, n, ind, ind, a[ind]);
				seg.upd(1, 1, n, ind+1, (stk.size() ? stk.top()-1 : n), -a[ind]);
			}

			seg.upd(1, 1, n, ptr+1, (stk.size() ? stk.top()-1 : n), a[ptr]);
			stk.push(ptr);
		}

		if (seg.query(1, 1, n, l, r) > k) ans[qry[i].ind] = 0;
		else ans[qry[i].ind] = 1;
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
