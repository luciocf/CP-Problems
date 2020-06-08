// Codeforces 675E - Trains and Statistic
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const long long inf = 1e18+10;

int a[maxn];
long long tree[4*maxn];

void upd(int node, int l, int r, int pos, long long v)
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

long long query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
		scanf("%d", &a[i]);

	long long ans = 0;

	upd(1, 1, n, n, n);

	for (int i = n-1; i >= 1; i--)
	{
		long long x = 1ll*(n-i-a[i]) + query(1, 1, n, i+1, a[i]);

		upd(1, 1, n, i, x+1ll*i);

		ans += x;
	}

	printf("%lld\n", ans);
}
