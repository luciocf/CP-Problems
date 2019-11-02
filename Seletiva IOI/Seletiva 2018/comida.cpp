// Seletiva IOI 2018 - Competição de Comida
// Lúcio Cardoso

// Sadly there's no OJ to submit it yet, so it's untested for now :(

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

int n;
int a[maxn], soma[maxn];

ll tree[4*maxn], tree2[4*maxn], lazy[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = soma[l];
		tree2[node] = a[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = min(tree[2*node], tree[2*node+1]);
	tree2[node] = tree2[2*node]+tree2[2*node+1];
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
		lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

	tree[node] += lazy[node];
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

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

void upd_soma(int node, int l, int r, int pos, ll v)
{
	if (l == r)
	{
		tree2[node] += v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd_soma(2*node, l, mid, pos, v);
	else upd_soma(2*node+1, mid+1, r, pos, v);

	tree2[node] = tree2[2*node]+tree2[2*node+1];
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

ll query_soma(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree2[node];

	int mid = (l+r)>>1;

	return query_soma(2*node, l, mid, a, b)+query_soma(2*node+1, mid+1, r, a, b);
}

int find_left(int node, int l, int r, ll v)
{
	flush(node, l, r);
	if (l == r) return l;

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[2*node] == v) return find_left(2*node, l, mid, v);
	return find_left(2*node+1, mid+1, r, v);
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
	{
		int t, g;
		scanf("%d %d", &t, &g);

		if (t == 1) a[i] = -g;
		else a[i] = g;

		soma[i] = soma[i-1]+a[i];
	}

	build(1, 1, n);

	for (int i = 0; i <= q; i++)
	{
		if (i > 0)
		{
			int op, pos, g;
			scanf("%d %d %d", &op, &pos, &g);

			if (op == 1)
			{
				upd(1, 1, n, pos, n, 1ll*-g);
				upd_soma(1, 1, n, pos, 1ll*-g);
			}
			else
			{
				upd(1, 1, n, pos, n, 1ll*g);
				upd_soma(1, 1, n, pos, 1ll*g);
			}
		}

		flush(1, 1, n);
		if (tree[1] >= 0)
		{
			printf("1\n");
			continue;
		}

		int opt = find_left(1, 1, n, query(1, 1, n, 1, n-1))+1;

		if (query_soma(1, 1, n, 1, n)+query(1, 1, n, 1, opt-1)-query_soma(1, 1, n, 1, opt-1) < 0)
		{
			printf("0\n");
			continue;
		}

		if (query(1, 1, n, opt, n)-query_soma(1, 1, n, 1, opt-1) < 0)
		{
			printf("0\n");
			continue;
		}

		printf("%d\n", opt);
	}
}
