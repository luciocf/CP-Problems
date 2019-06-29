// COI 2014 - Krave
// Lúcio Cardoso

// Solution is the same as this one: http://hsin.hr/2014/ (Final Exam #2)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

typedef long long ll;

set<int> tree[2][4*maxn];

int n, A, B;

void upd(int node, int l, int r, int a, int b, int v, bool q)
{
	if (l > r) return;
	if (l > b || r < a) return;

	if (l >= a && r <= b)
	{
		tree[q][node].insert(v);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v, q); upd(2*node+1, mid+1, r, a, b, v, q);
}

// rightmost
int query1(int node, int l, int r, int pos, int x, bool q)
{
	if (l > r) return 0;
	int ans = 0;

	set<int>::iterator it = tree[q][node].upper_bound(x);
	if (tree[q][node].size() > 0 && it != tree[q][node].begin())
	{
		--it;
		ans = *it;
	}

	if (l == r) return ans;

	int mid = (l+r)>>1;

	if (pos <= mid) return max(ans, query1(2*node, l, mid, pos, x, q));
	return max(ans, query1(2*node+1, mid+1, r, pos, x, q));
}

// leftmost
int query2(int node, int l, int r, int pos, int x, bool q)
{
	if (l > r) return inf;
	int ans = inf;

	set<int>::iterator it = tree[q][node].lower_bound(x);
	if (tree[q][node].size() > 0 && it != tree[q][node].end())
		ans = *it;

	if (l == r) return ans;

	int mid = (l+r)>>1;

	if (pos <= mid) return min(ans, query2(2*node, l, mid, pos, x, q));
	return min(ans, query2(2*node+1, mid+1, r, pos, x, q));
}

int main(void)
{
	scanf("%d %d %d", &A, &B, &n);

	for (int i = 1; i <= n; i++)
	{
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);

		if (d == 1)
		{
			int l = query1(1, 1, B, y, x-1, 0);
			int r = min(A, query2(1, 1, B, y, x+1, 0));

			int h1 = min(B, query2(1, 1, A, x, y+1, 1));
			int h2 = query1(1, 1, A, x, y-1, 1);

			ll area1 = 1ll*(r-l)*(h1-y), area2 = 1ll*(r-l)*(y-h2);
			printf("%lld %lld\n", min(area1, area2), max(area1, area2));

			upd(1, 1, A, l, r, y, 1);
		}
		else
		{
			int l = query1(1, 1, A, x, y-1, 1);
			int r = min(B, query2(1, 1, A, x, y+1, 1));

			int h1 = min(A, query2(1, 1, B, y, x+1, 0));
			int h2 = query1(1, 1, B, y, x-1, 0);

			ll area1 = 1ll*(r-l)*(h1-x), area2 = 1ll*(r-l)*(x-h2);
			printf("%lld %lld\n", min(area1, area2), max(area1, area2));

			upd(1, 1, B, l, r, x, 0);
		}
	}
}
