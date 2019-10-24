// BOI 2010 - Printed Circuit Board
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

typedef pair<int, int> pii;

pii a[maxn];

int last[maxn];
int ans[maxn];

int tree[4*maxn];

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

int query(int node, int l, int r, int x)
{
	if (l == r)
	{
		if (tree[node] <= x) return l;
		return -1;
	}

	int mid = (l+r)>>1;

	if (tree[2*node] <= x) return query(2*node, l, mid, x);
	return query(2*node+1, mid+1, r, x);
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
		int mex = query(1, 1, n, a[i].second);

		ans[i] = mex, last[mex] = max(last[mex], a[i].second);
		upd(1, 1, n, mex, last[mex]);
	}

	int ansF = 0;
	for (int i = 1; i <= n; i++)
		ansF = max(ansF, ans[i]);

	printf("%d\n", ansF);
}
