// IZhO 2019 - Bigger Segments
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef long long ll;
typedef pair<int, ll> pii; 

const int maxn = 5e5+10;
const ll inf = 1e18+10;

int a[maxn];
ll pref[maxn];

pii dp[maxn];
ll v[maxn];

struct SegmentTree
{
	ll tree[4*maxn];
 
	void upd(int node, int l, int r, int pos, ll v)
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
 
	int query(int node, int l, int r, int a, int b, ll v)
	{
		if (l > b || r < a || tree[node] > v) return -1;
		if (l == r) return l;
 
		int mid = (l+r)>>1;
 
		int p1 = query(2*node+1, mid+1, r, a, b, v);
 
		if (p1 == -1) return query(2*node, l, mid, a, b, v);
		return p1;
	}
} seg;

int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pref[i] = pref[i-1] + 1ll*a[i];
	}
 
	dp[1] = {1, a[1]+pref[1]};
 	seg.upd(1, 1, n, 1, dp[1].ss);

 	int l1 = 0, r1 = 0, l2 = 1, r2 = 1;

	for (int i = 2; i <= n; i++)
	{
		int p1 = seg.query(1, 1, n, l1, r1, pref[i]);
		int p2 = seg.query(1, 1, n, l2, r2, pref[i]);

		if (p2 != -1)
		{
			dp[i].ff = dp[p2].ff+1;
			dp[i].ss = 2*pref[i] - pref[p2];

			l1 = l2, r1 = r2;
			l2 = r2 = i;
		}
		else
		{
			dp[i].ff = dp[p1].ff+1;
			dp[i].ss = 2*pref[i] - pref[p1];

			++r2;
		}

		seg.upd(1, 1, n, i, dp[i].ss);
	}
 
	printf("%d\n", dp[n].ff);
}
