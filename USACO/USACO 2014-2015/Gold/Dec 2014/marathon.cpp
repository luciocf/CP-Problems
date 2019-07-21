// USACO Gold Dec 2014 - Marathon
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n;
int x[maxn], y[maxn];

int bit[maxn];
int tree[4*maxn];

void upd_bit(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		if (l > n-2) tree[node] = inf;
		else
		{
			int k = abs(x[l+2]-x[l]) + abs(y[l+2]-y[l]);
			k -= (abs(x[l+2]-x[l+1]) + abs(y[l+2]-y[l+1]) + abs(x[l+1]-x[l]) + abs(y[l+1]-y[l]));

			tree[node] = k;
		}

		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

void upd(int node, int l, int r, int pos)
{
	if (l == r)
	{
		if (l > n-2) tree[node] = inf;
		else
		{
			int k = abs(x[l+2]-x[l]) + abs(y[l+2]-y[l]);
			k -= (abs(x[l+2]-x[l+1]) + abs(y[l+2]-y[l+1]) + abs(x[l+1]-x[l]) + abs(y[l+1]-y[l]));

			tree[node] = k;
		}

		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos);
	else upd(2*node+1, mid+1, r, pos);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

int query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b)); 
}

int main(void)
{
	freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);
	
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &x[i], &y[i]);

	for (int i = 1; i < n; i++)
		upd_bit(i, abs(x[i]-x[i+1]) + abs(y[i]-y[i+1]));

	build(1, 1, n);

	while (q--)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'U')
		{
			int pos, a, b;
			scanf("%d %d %d", &pos, &a, &b);

			upd_bit(pos, -abs(x[pos]-x[pos+1])-abs(y[pos]-y[pos+1]));
			if (pos > 1)
				upd_bit(pos-1, -abs(x[pos-1]-x[pos])-abs(y[pos-1]-y[pos]));

			x[pos] = a, y[pos] = b;

			upd(1, 1, n, pos);
			if (pos > 2)
				upd(1, 1, n, pos-2);
			if (pos > 1)
				upd(1, 1, n, pos-1);

			upd_bit(pos, abs(x[pos]-x[pos+1])+abs(y[pos]-y[pos+1]));
			if (pos > 1)
				upd_bit(pos-1, abs(x[pos-1]-x[pos])+abs(y[pos-1]-y[pos]));
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			int ans = soma(r-1)-soma(l-1);

			ans = min(ans, ans+query(1, 1, n, l, r-2));

			printf("%d\n", ans);
		}
	}
}
