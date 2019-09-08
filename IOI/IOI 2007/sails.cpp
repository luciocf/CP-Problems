// IOI 2007 - Sails
// Lúcio Cardoso

// Solution: https://ioinformatics.org/files/ioi2007solutions.pdf

// After the greedy observation, the problem has a solution similar to this
// one: https://csacademy.com/contest/round-41/task/candles/

#include <bits/stdc++.h>

#define mx first
#define mn second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1e9+10;

pii a[maxn];

pii tree[4*maxn];
int lazy[4*maxn];

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node].mx += lazy[node];
	tree[node].mn += lazy[node];
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

	tree[node].mx = max(tree[2*node].mx, tree[2*node+1].mx);
	tree[node].mn = min(tree[2*node].mn, tree[2*node+1].mn);
}

int get(int node, int l, int r, int pos)
{
	flush(node, l, r);
	if (l == r) return tree[node].mn;

	int mid = (l+r)>>1;

	if (pos <= mid) return get(2*node, l, mid, pos);
	return get(2*node+1, mid+1, r, pos);
}

int query1(int node, int l, int r, int v)
{
	flush(node, l, r);
	if (l == r) return l;

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[2*node].mn <= v) return query1(2*node, l, mid, v);
	return query1(2*node+1, mid+1, r, v);
}

int query2(int node, int l, int r, int v)
{
	flush(node, l, r);
	if (l == r) return l;

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[2*node+1].mx >= v) return query2(2*node+1, mid+1, r, v);
	return query2(2*node, l, mid, v);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);

	sort(a+1, a+n+1);

	for (int i = 1; i <= n; i++)
	{
		int h = a[i].first, k = a[i].second;

		int x = get(1, 1, maxn-1, h-k+1);

		int p1 = query1(1, 1, maxn-1, x);
		int p2 = min(h, query2(1, 1, maxn-1, x));

		if (p2 < h) upd(1, 1, maxn-1, p2+1, h, 1);

		int r = k-(h-p2);

		upd(1, 1, maxn-1, p1, p1+r-1, 1);
	}

	long long ans = 0;

	for (int i = 1; i < maxn; i++)
	{
		long long x = get(1, 1, maxn-1, i);

		ans += ((x*(x-1ll))/2ll);
	}

	printf("%lld\n", ans);
}
