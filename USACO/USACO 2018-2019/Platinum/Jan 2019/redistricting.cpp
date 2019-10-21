// USACO 2018/2019 - Redistricting
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 6e5+10;

int n, k;
int a[maxn], dif[maxn];

int ans[maxn];

int tree[4*maxn];

multiset<int> st[maxn];

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node] = v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node] = min(tree[2*node], tree[2*node+1]); 
}

int query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return 1e9+10;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);

	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		char c;
		scanf(" %c", &c);

		if (c == 'G') a[i] = -1;
		else a[i] = 1;

		dif[i] = dif[i-1]+a[i];
	}

	for (int i = 0; i < 4*maxn; i++)
		tree[i] = 1e9+10;

	for (int i = 0; i <= n; i++)
		dif[i] += n;

	st[n].insert(0);
	upd(1, 0, 2*n, dif[0], 0);

	for (int i = 1; i <= k; i++)
	{
		ans[i] = query(1, 0, 2*n, 0, dif[i]-1);
		ans[i] = min(ans[i], 1+query(1, 0, 2*n, dif[i], 2*n));

		st[dif[i]].insert(ans[i]);
		upd(1, 0, 2*n, dif[i], *st[dif[i]].begin());
	}

	for (int i = k+1; i <= n; i++)
	{
		auto it = st[dif[i-k-1]].find(ans[i-k-1]);
		st[dif[i-k-1]].erase(it);

		if (st[dif[i-k-1]].size() == 0)
			upd(1, 0, 2*n, dif[i-k-1], 1e9+10);
		else
			upd(1, 0, 2*n, dif[i-k-1], *st[dif[i-k-1]].begin());

		ans[i] = query(1, 0, 2*n, 0, dif[i]-1);
		ans[i] = min(ans[i], 1+query(1, 0, 2*n, dif[i], 2*n));

		st[dif[i]].insert(ans[i]);
		upd(1, 0, 2*n, dif[i], *st[dif[i]].begin());
	}

	printf("%d\n", ans[n]);
}
