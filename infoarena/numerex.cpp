// infoarena - Numerex
// Lúcio Cardoso

// Solution: http://cfrp.azurewebsites.net/blog/entry/44478?#comment-290057

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

struct Lazy
{
	ll k, prod;
} lazy[4*maxn];

ll tree[4*maxn];

int n, m;

void flush(int node, int l, int r)
{
	if (!lazy[node].k) return;

	if (l != r)
	{
		lazy[2*node].k += lazy[node].k;
		lazy[2*node+1].k += lazy[node].k;

		int mid = (l+r)>>1;

		lazy[2*node].prod += lazy[node].prod;
		lazy[2*node+1].prod += lazy[node].prod + lazy[node].k * 1ll*(mid-l+1);
	}

	tree[node] += 1ll*lazy[node].k*((r-l)*(r-l+1))/2ll + 1ll*lazy[node].prod*(r-l+1ll);
	lazy[node] = {0, 0};
}

void upd(int node, int l, int r, int a, int b, int k)
{
	flush(node, l, r);

	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		lazy[node].k = k;
		lazy[node].prod = 1ll*(l-a+1)*k;
		flush(node, l, r);

		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, k); upd(2*node+1, mid+1, r, a, b, k);

	tree[node] = tree[2*node]+tree[2*node+1];
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);

	if (l > b || r < a) return 0;

	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return query(2*node, l, mid, a, b)+query(2*node+1, mid+1, r, a, b);
}

int main(void)
{
	freopen("numerex.in", "r", stdin);
	freopen("numerex.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);

		if (!op)
		{
			int l, x, k;
			scanf("%d %d %d", &l, &x, &k);

			upd(1, 1, n, l, l+x-1, k);
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			printf("%lld\n", query(1, 1, n, l, r));
		}
	}
}
