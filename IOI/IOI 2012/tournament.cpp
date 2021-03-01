// IOI 2012 - Jousting Tournament
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e5+10;
 
int a[maxn];
int ql[maxn], qr[maxn];
 
struct LazySegmentTree
{
	int tree[4*maxn];
	bool lazy[4*maxn];
 
	void build(int node, int l, int r)
	{
		tree[node] = r-l+1, lazy[node] = 0;
		if (l == r) return;
 
		int mid = (l+r)>>1;
 
		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}
 
	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;
 
		if (l != r) lazy[2*node] = lazy[2*node+1] = 1;
 
		tree[node] = 0;
		lazy[node] = 0;
	}
 
	void upd(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > b || r < a) return;
 
		if (l >= a && r <= b)
		{
			lazy[node] = 1;
			flush(node, l, r);
			return;
		}
 
		int mid = (l+r)>>1;
 
		upd(2*node, l, mid, a, b); upd(2*node+1, mid+1, r, a, b);
 
		tree[node] = tree[2*node] + tree[2*node+1]; 
	}
 
	int get(int node, int l, int r, int p)
	{
		flush(node, l, r);
		if (l == r) return l;
 
		int mid = (l+r)>>1;
 
		flush(2*node, l, mid); flush(2*node+1, mid+1, r);
 
		if (tree[2*node] >= p) return get(2*node, l, mid, p);
		return get(2*node+1, mid+1, r, p-tree[2*node]);
	}
} seg;
 
int ans_l[maxn], ans_r[maxn];
 
struct SegmentTree
{
	vector<int> tree[4*maxn][2];
 
	void upd(int node, int l, int r, int a, int b)
	{
		if (l > b || r < a) return;
 
		if (l >= a && r <= b)
		{
			tree[node][0].push_back(-a);
			tree[node][1].push_back(b);
			return;
		}
 
		int mid = (l+r)>>1;
 
		upd(2*node, l, mid, a, b); upd(2*node+1, mid+1, r, a, b);
	}
 
	int getl(int node, int l, int r, int pos, int k)
	{
		int mid = (l+r)>>1;
 
		int v = 1;
 
		if (l != r)
		{
			v = (pos <= mid ? getl(2*node, l, mid, pos, k) : getl(2*node+1, mid+1, r, pos, k));
		}
 
		if (!v) return 0;
 
		if (tree[node][0].size() == 0 || -tree[node][0].back() > k)
		{
			ans_l[pos] += tree[node][0].size();
			return 1;
		}
 
		int x = (int)(lower_bound(tree[node][0].begin(), tree[node][0].end(), -k) - tree[node][0].begin());
 
		ans_l[pos] += x;
		return 0;
	}
 
	int getr(int node, int l, int r, int pos, int k)
	{
		int mid = (l+r)>>1;
 
		int v = 1;
 
		if (l != r)
		{
			v = (pos <= mid ? getr(2*node, l, mid, pos, k) : getr(2*node+1, mid+1, r, pos, k));
		}
 
		if (!v) return 0;
 
		if (tree[node][1].size() == 0 || tree[node][1].back() < k)
		{
			ans_r[pos] += tree[node][1].size();
			return 1;
		}
 
		int x = (int)(lower_bound(tree[node][1].begin(), tree[node][1].end(), k) - tree[node][1].begin());
 
		ans_r[pos] += x;
		return 0;
	}
} seg2;
 
int GetBestPosition(int n, int q, int R, int *K, int *S, int *E)
{
	for (int i = 0; i < n-1; i++)
		a[i+1] = K[i];
 
	for (int i = 0; i < q; i++)
		ql[i+1] = S[i]+1, qr[i+1] = E[i]+1;
 
	seg.build(1, 1, n);
 
	for (int i = 1; i <= q; i++)
	{
		int l = (ql[i] == 1 ? 1 : seg.get(1, 1, n, ql[i]-1)+1);
		int r = seg.get(1, 1, n, qr[i]);
 
		if (l <= r-1) seg.upd(1, 1, n, l, r-1);
		seg2.upd(1, 1, n, l, r);
	}
 
	int prim = 0;
 
	for (int i = 1; i <= n; i++)
	{
		seg2.getl(1, 1, n, i, prim);
 
		if (a[i] > R) prim = i;
	}
 
	prim = n+1;
 
	for (int i = n; i >= 1; i--)
	{
		seg2.getr(1, 1, n, i, prim);
 
		if (a[i-1] > R) prim = i;
	}
 
	int best = 1, mx = 0;
 
	for (int i = 1; i <= n; i++)
		if (min(ans_l[i], ans_r[i]) > mx)
			best = i, mx = min(ans_l[i], ans_r[i]);
 
	return best-1;
}
