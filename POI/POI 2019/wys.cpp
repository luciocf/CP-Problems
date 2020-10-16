// POI 2019 - Auto Racing
// Lúcio Cardoso

// Solution is pretty much the same as the one in: https://github.com/Kshitij-789/CompetitiveProgramming/blob/master/Olympiad/POI/POI%2019-wys.cpp

// However, I didn't notice that to answer queries we only need to check the condition between
// the values > a_i, I also checked the values < a_i, so my query was a bit more complicated.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;
const ll inf = 2e18+10;

int n;
int a[maxn];

struct SegmentTree
{
	ll tree[3][4*maxn], lazy[4*maxn];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[0][node] = tree[1][node] = a[l], tree[2][node] = a[l]-l;
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		tree[0][node] = max(tree[0][2*node], tree[0][2*node+1]);
		tree[1][node] = min(tree[1][2*node], tree[1][2*node+1]);
		tree[2][node] = max(tree[2][2*node], tree[2][2*node+1]);
	}

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}

		tree[0][node] += lazy[node];
		tree[1][node] += lazy[node];
		tree[2][node] += lazy[node];
		lazy[node] = 0;
	}

	void upd(int node, int l, int r, int a, int b, ll v)
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

		tree[0][node] = max(tree[0][2*node], tree[0][2*node+1]);
		tree[1][node] = min(tree[1][2*node], tree[1][2*node+1]);
		tree[2][node] = max(tree[2][2*node], tree[2][2*node+1]);
	}

	int get_mx(int node, int l, int r, ll v)
	{
		flush(node, l, r);
		if (l == r) return (tree[0][node] >= v ? l : -1);

		int mid = (l+r)>>1;

		flush(2*node, l, mid); flush(2*node+1, mid+1, r);

		if (tree[0][2*node] >= v) return get_mx(2*node, l, mid, v);
		return get_mx(2*node+1, mid+1, r, v);
	}

	int get_mn(int node, int l, int r, ll v)
	{
		flush(node, l, r);
		if (l == r) return (tree[1][node] <= v ? l : -1);

		int mid = (l+r)>>1;

		flush(2*node, l, mid); flush(2*node+1, mid+1, r);

		if (tree[1][2*node+1] <= v) return get_mn(2*node+1, mid+1, r, v);
		return get_mn(2*node, l, mid, v);
	}

	ll query(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > r || l > b || r < a) return -inf;
		if (l >= a && r <= b) return tree[2][node];

		int mid = (l+r)>>1;

		return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
	}

	int get_ans(int node, int l, int r, ll mx_l, ll mx_r)
	{
		flush(node, l, r);
		if (max(mx_l, mx_r + 1) > tree[0][node]) return -1;

		if (l == r) return l;

		int mid = (l+r)>>1;

		flush(2*node, l, mid); flush(2*node+1, mid+1, r);

		int p1 = get_ans(2*node, l, mid, mx_l, max(mx_r, tree[2][2*node+1]));

		return (p1 == -1 ? get_ans(2*node+1, mid+1, r, max(mx_l, tree[2][2*node]), mx_r) : p1);
	}
} seg;

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	seg.build(1, 1, n);

	while (q--)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'B')
		{
			ll x, y;
			scanf("%lld %lld", &x, &y);

			int pos = seg.get_mx(1, 1, n, x);
			if (pos == -1) continue;

			seg.upd(1, 1, n, pos, n, y);
		}
		else if (op == 'K')
		{
			ll x, y;
			scanf("%lld %lld", &x, &y);

			int pos = seg.get_mn(1, 1, n, x);
			if (pos == -1) continue;

			seg.upd(1, 1, n, 1, pos, -y);
		}
		else
		{
			int ans = seg.get_ans(1, 1, n, -inf, -inf);

			if (ans == -1) printf("0\n");
			else printf("%d\n", n - ans + 1);
		}
	}
}
