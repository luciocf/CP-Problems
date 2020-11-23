// Codeforces 515E - Drazil and Park
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

int d[maxn], h[maxn];

ll pref[maxn], suf[maxn];
ll max_pref[maxn], max_suf[maxn];

struct SegmentTree
{
	struct Node
	{
		ll mx1, mx2, ans;
	} tree[4*maxn];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node] = {-pref[l]+2ll*h[l], pref[l]+2ll*h[l], 0};
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		tree[node].mx1 = max(tree[2*node].mx1, tree[2*node+1].mx1);
		tree[node].mx2 = max(tree[2*node].mx2, tree[2*node+1].mx2);
		tree[node].ans = max({tree[2*node].ans, tree[2*node+1].ans, tree[2*node+1].mx2+tree[2*node].mx1});
	}

	Node query(int node, int l, int r, int a, int b)
	{
		if (l > b || r < a) return {-inf, -inf, -inf};
		if (l >= a && r <= b) return tree[node];

		int mid = (l+r)>>1;

		auto p1 = query(2*node, l, mid, a, b), p2 = query(2*node+1, mid+1, r, a, b);

		return {max(p1.mx1, p2.mx1), max(p1.mx2, p2.mx2), max({p1.ans, p2.ans, p2.mx2+p1.mx1})};
	}
} seg;

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &h[i]);

	max_pref[1] = 2ll*h[1];

	for (int i = 2; i <= n; i++)
	{
		pref[i] = pref[i-1] + 1ll*d[i-1];
		max_pref[i] = max(max_pref[i-1], 2ll*h[i]+pref[i]);
	}

	for (int i = n; i >= 1; i--)
	{
		suf[i] = suf[i+1] + 1ll*d[i];
		max_suf[i] = max(max_suf[i+1], 2ll*h[i]+suf[i]);
	}

	seg.build(1, 1, n);

	while (m--)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		if (l <= r)
		{
			ll ans = -inf;

			if (l > 2) ans = max(ans, seg.query(1, 1, n, 1, l-1).ans);
			if (r < n-1) ans = max(ans, seg.query(1, 1, n, r+1, n).ans);

			if (l > 1 && r < n) ans = max(ans, max_pref[l-1] + max_suf[r+1]);

			printf("%lld\n", ans);
		}
		else
		{
			swap(l, r);
			l++, r--;

			printf("%lld\n", seg.query(1, 1, n, l, r).ans);
		}
	}
}
