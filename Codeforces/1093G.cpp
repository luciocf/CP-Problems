// Codeforces 1093G - Multidimensional Queries
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int n, k;

int a[maxn][6];

struct SegmentTree
{
	int tree[1<<5][3*maxn];

	void init(void)
	{
		for (int i = 0; i < (1<<5); i++)
			for (int j = 0; j < 3*maxn; j++)
				tree[i][j] = -inf;
	}

	void upd(int node, int l, int r, int k, int pos, int v)
	{
		if (l == r)
		{
			tree[k][node] = v;
			return;
		}

		int mid = (l+r)>>1;

		if (pos <= mid) upd(2*node, l, mid, k, pos, v);
		else upd(2*node+1, mid+1, r, k, pos, v);

		tree[k][node] = max(tree[k][2*node], tree[k][2*node+1]);
	}

	int query(int node, int l, int r, int k, int a, int b)
	{
		if (l > b || r < a) return -inf;
		if (l >= a && r <= b) return tree[k][node];

		int mid = (l+r)>>1;

		return max(query(2*node, l, mid, k, a, b), query(2*node+1, mid+1, r, k, a, b));
	}
} seg;

void add(int ind)
{
	for (int mask = 0; mask < (1<<k); mask++)
	{
		int x = 0;

		for (int i = 0; i < k; i++)
		{
			if (mask&(1<<i)) x += a[ind][i];
			else x -= a[ind][i];
		}

		seg.upd(1, 1, n, mask, ind, x);
	}
}

int get(int l, int r)
{
	int ans = 0;

	for (int mask = 0; mask < (1<<k); mask++)
	{
		int mask2 = mask^((1<<k)-1);

		ans = max(ans, seg.query(1, 1, n, mask, l, r) + seg.query(1, 1, n, mask2, l, r));
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &k);

	seg.init();

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < k; j++)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= n; i++)
		add(i);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int ind;
			scanf("%d", &ind);

			for (int i = 0; i < k; i++)
				scanf("%d", &a[ind][i]);

			add(ind);
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			printf("%d\n", get(l, r));
		}
	}
}
