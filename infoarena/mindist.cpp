// infoarena - Mindist
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int add = 5e4+10;

set<int> tree[4*maxn];

void upd(int node, int l, int r, int pos, int v)
{
	tree[node].insert(v);

	if (l == r) return;

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);
}

bool query(int node, int l, int r, int a, int b, int c, int d)
{
	if (l > b || r < a) return false;

	if (l >= a && r <= b)
	{
		auto it = tree[node].lower_bound(c);

		if (it == tree[node].end() || *it > d) return false;
		return true;
	}

	int mid = (l+r)>>1;

	return (query(2*node, l, mid, a, b, c, d) || query(2*node+1, mid+1, r, a, b, c, d));
}

int main(void)
{
	freopen("mindist.in", "r", stdin); freopen("mindist.out", "w", stdout);
	
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);

		int a = x-y + add, b = x+y;

		int ini = 0, fim = maxn, ans = maxn;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (query(1, 0, maxn-1, a-mid, a+mid, b-mid, b+mid)) ans = mid, fim = mid-1;
			else ini = mid+1;
		}

		if (i == 1) printf("0\n");
		else printf("%d\n", ans);

		upd(1, 0, maxn-1, a, b);
	}
}
