// USACO 2015/2016 - Mowing the Field
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

typedef pair<int, int> pii;

struct Event
{
	int type; // 0 - right hor; 1 - vert; 2 - left hor
	int t;
	int x, y;
	int l, r;
} event[maxn];

struct Node
{
	int v;
	Node *l, *r;

	Node()
	{
		v = 0;
		l = r = NULL;
	}
} *bit[maxn];

pii a[maxn];

bool comp(Event a, Event b)
{
	if (a.x == b.x) return a.type < b.type;
	return a.x < b.x;
}

void upd(Node *node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		node->v += v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid)
	{
		if (!node->l) node->l = new Node();
		upd(node->l, l, mid, pos, v);
	}
	else
	{
		if (!node->r) node->r = new Node();
		upd(node->r, mid+1, r, pos, v);
	}

	node->v = (node->l ? node->l->v : 0) + (node->r ? node->r->v : 0);
}

int query(Node *node, int l, int r, int a, int b)
{
	if (!node || l > b || r < a || l > r) return 0;
	if (l >= a && r <= b) return node->v;

	int mid = (l+r)>>1;

	return query(node->l, l, mid, a, b) + query(node->r, mid+1, r, a, b);
}

void build(void)
{
	for (int i = 0; i < maxn; i++)
		bit[i] = new Node();
}

void upd(int x, int y, int v)
{
	for (; x < maxn; x += (x&-x))
		upd(bit[x], 0, maxn-1, y, v);
}

long long query(int x, int l, int r)
{
	long long ans = 0;

	for (; x > 0; x -= (x&-x))
		ans += 1ll*query(bit[x], 0, maxn-1, l, r);

	return ans;
}

void compress(int n)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i].first] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i].first = mp[a[i].first];

	mp.clear();

	for (int i = 1; i <= n; i++)
		mp[a[i].second] = 0;

	aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i].second = mp[a[i].second];
}

int main(void)
{
	freopen("mowing.in", "r", stdin); freopen("mowing.out", "w", stdout);

	int n, T;
	scanf("%d %d", &n, &T);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);

	compress(n);

	int m = 0;

	for (int i = 1; i < n; i++)
	{
		if (a[i].first == a[i+1].first)
		{
			int mn = min(a[i].second, a[i+1].second);
			int mx = max(a[i].second, a[i+1].second);

			event[++m] = {1, i+1, a[i].first, -1, mn, mx};
		}
		else
		{
			if (a[i].first < a[i+1].first)
			{
				event[++m] = {2, i+1, a[i].first, a[i].second, -1, -1};
				event[++m] = {0, i+1, a[i+1].first, a[i+1].second, -1, -1};
			}
			else
			{
				event[++m] = {2, i+1, a[i+1].first, a[i+1].second, -1, -1};
				event[++m] = {0, i+1, a[i].first, a[i].second, -1, -1};
			}
		}
	}

	sort(event+1, event+m+1, comp);

	build();

	long long ans = 0;

	for (int i = 1; i <= m; i++)
	{
		if (event[i].type == 1)
		{
			ans += 1ll*(query(event[i].r-1, 0, event[i].t-T)-query(event[i].l, 0, event[i].t-T));

			ans += 1ll*(query(event[i].r-1, event[i].t+T, maxn-1)-query(event[i].l, event[i].t+T, maxn-1));
		}
		else if (event[i].type == 2) upd(event[i].y, event[i].t, 1);
		else upd(event[i].y, event[i].t, -1);
	}

	printf("%lld\n", ans);
}
