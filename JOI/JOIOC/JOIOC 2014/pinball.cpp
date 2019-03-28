// JOI Open Contest 2014 - Pinball
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;
const long long inf = 2e18+10;

typedef long long ll;

int ind, m;
int l[maxn], r[maxn], p[maxn], d[maxn];

ll tree[4*maxn];

ll dp[2][maxn];

map<int, int> mp;

void compress(int n)
{
	mp[1] = mp[m] = 0;
	for (int i = 1; i <= n; i++)
		mp[l[i]] = mp[r[i]] = mp[p[i]] = 0;

	for (auto &x: mp)
		x.second = ++ind;

	m = mp[m];
	for (int i = 1; i <= n; i++)
		l[i] = mp[l[i]], r[i] = mp[r[i]], p[i] = mp[p[i]];
}

void init(void)
{
	for (int i = 0; i < 4*maxn; i++)
		tree[i] = inf;
}

void upd(int node, int l, int r, int pos, ll v)
{
	if (l == r)
	{
		tree[node] = min(tree[node], v);
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

ll query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

int main(void)
{
	int n;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d %d %d", &l[i], &r[i], &p[i], &d[i]);

		dp[0][i] = dp[1][i] = inf;
	}

	compress(n);
	init();

	for (int i = 1; i <= n; i++)
	{
		if (l[i] == 1) dp[0][i] = d[i];
		else dp[0][i] = 1ll*d[i] + query(1, 1, ind, l[i], r[i]);

		upd(1, 1, ind, p[i], dp[0][i]);
	}

	init();

	for (int i = 1; i <= n; i++)
	{
		if (r[i] == m) dp[1][i] = d[i];
		else dp[1][i] = 1ll*d[i] + query(1, 1, ind, l[i], r[i]);

		upd(1, 1, ind, p[i], dp[1][i]);
	}

	ll ans = inf;
	for (int i = 1; i <= n; i++)
		if (dp[0][i] < inf && dp[1][i] < inf)
			ans = min(ans, dp[0][i]+dp[1][i]-1ll*d[i]);

	if (ans == inf) printf("-1\n");
	else printf("%lld\n", ans);
}
