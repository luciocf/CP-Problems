// Codeforces 1217E - Sum Queries?
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;
const int inf = 2e9+10;

int n;
int a[maxn];

int best[40];

struct SegmentTree
{
	int tree[4*maxn][40];
	ll ans[4*maxn];

	void join(int node, int l, int r)
	{
		ans[node] = min(ans[2*node], ans[2*node+1]);

		for (int i = 0; i < 40; i++)
		{
			ans[node] = min(ans[node], 1ll*tree[2*node][i] + 1ll*tree[2*node+1][i]);
			tree[node][i] = min(tree[2*node][i], tree[2*node+1][i]);
		}
	}

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			ans[node] = inf;
			for (int i = 0; i < 40; i++)
				tree[node][i] = inf;

			int x = a[l], ind = 0;

			while (x > 0)
			{
				if (x%10) tree[node][ind] = a[l];

				x /= 10, ind++;
			}

			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		join(node, l, r);
	}

	void upd(int node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			for (int i = 0; i < 40; i++)
				tree[node][i] = inf;

			int x = v, ind = 0;

			while (x > 0)
			{
				if (x%10) tree[node][ind] = v;

				x /= 10, ind++;
			}

			return;
		}

		int mid = (l+r)>>1;

		if (pos <= mid) upd(2*node, l, mid, pos, v);
		else upd(2*node+1, mid+1, r, pos, v);

		join(node, l, r);
	}

	ll query(int node, int l, int r, int a, int b)
	{
		if (l > b || r < a) return inf;

		if (l >= a && r <= b)
		{
			ll mn = ans[node];

			for (int i = 0; i < 40; i++)
			{
				mn = min(mn, 1ll*best[i] + 1ll*tree[node][i]);
				best[i] = min(best[i], tree[node][i]);
			}

			return mn;
		}

		int mid = (l+r)>>1;

		return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
	}
} seg;

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	seg.build(1, 1, n);

	while (m--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int pos, v;
			scanf("%d %d", &pos, &v);

			seg.upd(1, 1, n, pos, v);
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			for (int i = 0; i < 40; i++)
				best[i] = inf;

			ll ans = seg.query(1, 1, n, l, r);

			if (ans == inf) printf("-1\n");
			else printf("%lld\n", ans);
		}
	}
}
