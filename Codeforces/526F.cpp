// Codeforces 526F - Pudding Monsters
// Lúcio Cardoso

// Solution is the same as the one using segment tree (mentioned in editorial)

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 3e5+10;
const int inf = 1e9+10;

struct SegmentTree
{
	pii tree[4*maxn];
	int lazy[4*maxn];

	void build(int node, int l, int r)
	{
		tree[node] = {inf, r-l+1};
		if (l == r) return;

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r)
			lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

		tree[node].ff += lazy[node];
		lazy[node] = 0;
	}

	void upd(int node, int l, int r, int a, int b, int v)
	{
		flush(node, l, r);
		if (l > r || l > b || r < a) return;

		if (l >= a && r <= b)
		{
			lazy[node] = v;
			flush(node, l, r);
			return;
		}

		int mid = (l+r)>>1;

		upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);

		tree[node].ff = min(tree[2*node].ff, tree[2*node+1].ff);
		tree[node].ss = 0;

		if (tree[2*node].ff == tree[node].ff) tree[node].ss += tree[2*node].ss;
		if (tree[2*node+1].ff == tree[node].ff) tree[node].ss += tree[2*node+1].ss;
	}
} seg;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);

		a[y] = x;
	}

	seg.build(1, 1, n);

	ll ans = 0;
	stack<pii> stk_mx, stk_mn;

	for (int i = 1; i <= n; i++)
	{
		seg.upd(1, 1, n, 1, i-1, -1); seg.upd(1, 1, n, i, i, -inf);

		while (stk_mx.size() && stk_mx.top().ff < a[i])
		{
			int r = stk_mx.top().ss, mx = stk_mx.top().ff;
			stk_mx.pop();

			int l = (stk_mx.size() ? stk_mx.top().ss+1 : 1);

			seg.upd(1, 1, n, l, r, a[i] - mx);
		}

		while (stk_mn.size() && stk_mn.top().ff > a[i])
		{
			int r = stk_mn.top().ss, mn = stk_mn.top().ff;
			stk_mn.pop();

			int l = (stk_mn.size() ? stk_mn.top().ss+1 : 1);

			seg.upd(1, 1, n, l, r, mn - a[i]);
		}

		stk_mx.push({a[i], i}); stk_mn.push({a[i], i});

		seg.flush(1, 1, n);
		ans += 1ll*seg.tree[1].ss;
	}

	printf("%lld\n", ans);
}
