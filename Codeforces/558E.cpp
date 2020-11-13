// Codeforces 558E - A Simple Task
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn];

	void build(int node, int l, int r)
	{
		lazy[node] = -1;
		if (l == r) return;

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}

	void flush(int node, int l, int r)
	{
		if (lazy[node] == -1) return;

		if (l != r)
			lazy[2*node] = lazy[node], lazy[2*node+1] = lazy[node];

		tree[node] = (r-l+1)*lazy[node];
		lazy[node] = -1;
	}

	void upd(int node, int l, int r, int a, int b, int v)
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

		tree[node] = tree[2*node] + tree[2*node+1];
	}

	int query(int node, int l, int r, int a, int b)
	{
		flush(node, l, r);
		if (l > b || r < a) return 0;
		if (l >= a && r <= b) return tree[node];

		int mid = (l+r)>>1;

		return query(2*node, l, mid, a, b) + query(2*node+1, mid+1, r, a, b);
	}
} seg[26];

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 0; i < 26; i++)
		seg[i].build(1, 1, n);

	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);

		seg[(int)(c-'a')].upd(1, 1, n, i, i, 1);
	}

	while (q--)
	{
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);

		int tot[26];

		for (int i = 0; i < 26; i++)
		{
			tot[i] = seg[i].query(1, 1, n, l, r);
			seg[i].upd(1, 1, n, l, r, 0);
		}

		if (k)
		{
			int pos = l;

			for (int i = 0; i < 26; i++)
			{
				if (tot[i]) seg[i].upd(1, 1, n, pos, pos+tot[i]-1, 1);

				pos += tot[i];
			}

			assert(pos == r+1);
		}
		else
		{
			int pos = l;

			for (int i = 25; i >= 0; i--)
			{
				if (tot[i]) seg[i].upd(1, 1, n, pos, pos+tot[i]-1, 1);

				pos += tot[i];
			}

			assert(pos == r+1);
		}
	}

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 26; j++)
			if (seg[j].query(1, 1, n, i, i))
				printf("%c", (char)('a'+j));

	printf("\n");
}
