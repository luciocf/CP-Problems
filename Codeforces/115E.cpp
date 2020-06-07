// Codeforces 115E - Linear Kingdom Races
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

struct Range
{
	int l, r, v;
} range[maxn];

ll dp[maxn];
ll pref[maxn];

ll tree[4*maxn], lazy[4*maxn];

bool comp(Range a, Range b) {return a.r < b.r;}

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

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return max(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);

		pref[i] = pref[i-1]+1ll*a;
	}

	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &range[i].l, &range[i].r, &range[i].v);

	sort(range+1, range+m+1, comp);

	int q = 0;

	for (int i = 1; i <= n; i++)
	{
		while (q < m && range[q+1].r == i)
		{
			++q;
			upd(1, 1, n, 1, range[q].l, range[q].v);
		}

		upd(1, 1, n, i, i, dp[max(0, i-2)] + pref[i-1]);

		dp[i] = max(dp[i-1], query(1, 1, n, 1, i) - pref[i]);
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dp[i]);

	printf("%lld\n", ans);
}
