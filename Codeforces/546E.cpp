// Codeforces 546E - Nastya Hasn't Written a Legend
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

struct SegmentTree
{
	ll tree[2][4*maxn], lazy[2][4*maxn];

	void flush(int node, int l, int r)
	{
		if (lazy[0][node] == inf && !lazy[1][node]) return;

		if (l != r)
		{
			if (lazy[0][node] != inf)
			{
				lazy[0][2*node] = lazy[0][node], lazy[1][2*node] = 0;
				lazy[0][2*node+1] = lazy[0][node], lazy[1][2*node+1] = 0;
			}
			else
			{
				if (lazy[0][2*node] != inf) lazy[0][2*node] += lazy[1][node];
				else lazy[1][2*node] += lazy[1][node];

				if (lazy[0][2*node+1] != inf) lazy[0][2*node+1] += lazy[1][node];
				else lazy[1][2*node+1] += lazy[1][node];
			}
		}

		if (lazy[0][node] != inf)
		{
			tree[0][node] = lazy[0][node];
			tree[1][node] = 1ll*(r-l+1)*lazy[0][node];
		}
		else
		{
			tree[0][node] += lazy[1][node];
			tree[1][node] += 1ll*(r-l+1)*lazy[1][node];
		}

		lazy[0][node] = inf, lazy[1][node] = 0;
	}

	void upd(int node, int l, int r, int a, int b, ll v, bool q)
	{
		if (l > r) return;
		flush(node, l, r);
		if (l > b || r < a) return;

		if (l >= a && r <= b)
		{
			if (q == 0)
			{
				lazy[0][node] = v;
				lazy[1][node] = 0;
			}
			else
			{
				if (lazy[0][node] != inf) lazy[0][node] += v;
				else lazy[1][node] += v;
			}

			flush(node, l, r);
			return;
		}

		int mid = (l+r)>>1;

		upd(2*node, l, mid, a, b, v, q); upd(2*node+1, mid+1, r, a, b, v, q);

		tree[0][node] = max(tree[0][2*node], tree[0][2*node+1]);
		tree[1][node] = tree[1][2*node] + tree[1][2*node+1];
	}

	ll query(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[1][node];

		int mid = (l+r)>>1;

		return query(2*node, l, mid, a, b) + query(2*node+1, mid+1, r, a, b);
	}

	int get(int node, int l, int r, int a, int b, ll v)
	{
		flush(node, l, r);
		if (l > b || r < a || tree[0][node] < v) return -1;

		if (l == r)
		{
			if (tree[0][node] >= v) return l;
			return -1;
		}

		int mid = (l+r)>>1;

		int p1 = get(2*node, l, mid, a, b, v);

		if (p1 == -1) return get(2*node+1, mid+1, r, a, b, v);
		return p1;
	}
} seg;

int n;
int a[maxn], k[maxn];
ll pref[maxn], pref2[maxn];

ll soma(int l, int r)
{
	return (seg.query(1, 1, n, l, r) + (pref2[r-1] - (l == 1 ? 0 : pref2[l-2])));
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < 4*n; i++)
		seg.lazy[0][i] = inf;

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		scanf("%d", &k[i]);
		pref[i] = pref[i-1] + 1ll*k[i];
	}
	pref[n] = pref[n-1];

	for (int i = 1; i <= n; i++)
		pref2[i] = pref2[i-1] + pref[i];

	for (int i = 1; i <= n; i++)
		seg.upd(1, 1, n, i, i, 1ll*a[i]-pref[i-1], 1);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		char op;
		scanf(" %c", &op);

		if (op == 's')
		{
			int l, r;
			scanf("%d %d", &l, &r);

			printf("%lld\n", soma(l, r));
		}
		else
		{
			int pos, x;
			scanf("%d %d", &pos, &x);

			seg.upd(1, 1, n, pos, pos, x, 1);

			int l = pos, r = seg.get(1, 1, n, pos+1, n, seg.query(1, 1, n, pos, pos));

			if (r == -1) r = n;
			else r--;

			seg.upd(1, 1, n, l+1, r, soma(l, l) - pref[l-1], 0);
		}
	}
}
