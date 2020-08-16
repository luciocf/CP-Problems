// Codeforces 817F - MEX Queries
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;

struct SegmentTree
{
	int tree[4*maxn], lazy[4*maxn];

	void flush(int node, int l, int r)
	{
		if (lazy[node] == 0) return;

		int mid = (l+r)>>1;

		if (l != r)
		{
			if (lazy[node] == 3)
			{
				if (lazy[2*node] == 1) lazy[2*node] = 2;
				else if (lazy[2*node] == 2) lazy[2*node] = 1;
				else if (lazy[2*node] == 3) lazy[2*node] = 0;
				else lazy[2*node] = 3;

				if (lazy[2*node+1] == 1) lazy[2*node+1] = 2;
				else if (lazy[2*node+1] == 2) lazy[2*node+1] = 1;
				else if (lazy[2*node+1] == 3) lazy[2*node+1] = 0;
				else lazy[2*node+1] = 3;
			}
			else lazy[2*node] = lazy[2*node+1] = lazy[node];
		}

		if (lazy[node] == 1) tree[node] = r-l+1;
		else if (lazy[node] == 2) tree[node] = 0;
		else tree[node] = (r-l+1)-tree[node];

		lazy[node] = 0;
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

		tree[node] = tree[2*node]+tree[2*node+1];
	}

	int get(int node, int l, int r)
	{
		flush(node, l, r);
		if (l == r) return l;

		int mid = (l+r)>>1;
		flush(2*node, l, mid); flush(2*node+1, mid+1, r);


		if (tree[2*node] != mid-l+1) return get(2*node, l, mid);
		return get(2*node+1, mid+1, r);
	}
} seg;

struct Query
{
	int op;
	ll l, r;
} qry[maxn];

map<ll, ll> mp, back;

void compress(int q)
{
	for (int i = 1; i <= q; i++)
	{
		mp[qry[i].l] = mp[qry[i].r] = 0;
		mp[qry[i].r+1] = 0;
	}

	int aux = 0;

	for (auto &x: mp)
	{
		x.second = ++aux;
		back[aux] = x.first;
	}
}

int main(void)
{
	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
		scanf("%d %lld %lld", &qry[i].op, &qry[i].l, &qry[i].r);

	compress(q);

	if (mp.find(1) == mp.end())
	{
		while (q--)
			printf("1\n");
		return 0;
	}

	for (int i = 1; i <= q; i++)
	{
		seg.upd(1, 1, maxn-1, mp[qry[i].l], mp[qry[i].r], qry[i].op);

		printf("%lld\n", back[seg.get(1, 1, maxn-1)]);
	}
}
