// USACO Plat Feb 2018 - Slingshot
// Lúcio Cardoso

// Solution: http://usaco.org/current/data/sol_slingshot_platinum_feb18.html

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 4e5+10;
const long long inf = 2e18+10;

struct Slingshot
{
	int x, y, c;
} op[maxn];

struct Event
{
	int x;
	int type, ind;
};

ll ans[maxn];

ll tree[3*maxn];

pii mp_op[maxn], mp_qry[maxn];

pii qry[maxn];

map<int, int> mp;

void clear(void)
{
	for (int i = 0; i < 3*maxn; i++)
		tree[i] = inf;
}

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node] = min(tree[node], 1ll*v);
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

ll query(int node, int l, int r, int a, int b)
{
	if (a > b) return inf;

	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}

bool comp(Event a, Event b)
{
	if (a.x == b.x) return a.type < b.type;
	return a.x < b.x;
}

void solve(int n, int m)
{
	vector<Event> sweep;

	for (int i = 1; i <= n; i++)
	{
		if (op[i].x > op[i].y) continue;

		sweep.push_back({op[i].x, 0, i});
		sweep.push_back({op[i].y, 1, i});
	}

	for (int i = 1; i <= m; i++)
	{
		if (qry[i].ff > qry[i].ss) continue;

		sweep.push_back({qry[i].ff, 2, i});
		sweep.push_back({qry[i].ss, 3, i});
	}

	sort(sweep.begin(), sweep.end(), comp);

	// in, out
	for (auto E: sweep)
	{
		int ind = E.ind;

		if (E.type == 0) upd(1, 1, maxn-1, mp_op[ind].ss, op[ind].c - op[ind].x - op[ind].y);

		if (E.type == 2)
		{
			int x = qry[ind].ff, y = qry[ind].ss;

			ans[ind] = min(ans[ind], 1ll*(y-x));

			ans[ind] = min(ans[ind], x+y+query(1, 1, maxn-1, mp_qry[ind].ff+1, mp_qry[ind].ss-1));
		}
	}

	clear();

	// in, in
	for (auto E: sweep)
	{
		int ind = E.ind;

		if (E.type == 0) upd(1, 1, maxn-1, mp_op[ind].ss, op[ind].c - op[ind].x + op[ind].y);

		if (E.type == 2)
		{
			int x = qry[ind].ff, y = qry[ind].ss;

			ans[ind] = min(ans[ind], 1ll*(y-x));

			ans[ind] = min(ans[ind], x-y+query(1, 1, maxn-1, mp_qry[ind].ss, maxn-1));
		}
	}

	clear();

	// out, out
	for (auto E: sweep)
	{
		int ind = E.ind;

		if (E.type == 1) upd(1, 1, maxn-1, mp_op[ind].ff, op[ind].c + op[ind].x - op[ind].y);

		if (E.type == 3)
		{
			int x = qry[ind].ff, y = qry[ind].ss;

			ans[ind] = min(ans[ind], 1ll*(y-x));

			ans[ind] = min(ans[ind], y-x+query(1, 1, maxn-1, mp_qry[ind].ff+1, mp_qry[ind].ss-1));
		}
	}

	clear();

	// out, in
	for (int i = sweep.size()-1; i >= 0; i--)
	{
		int ind = sweep[i].ind;
		int type = sweep[i].type;

		if (type == 1) upd(1, 1, maxn-1, mp_op[ind].ff, op[ind].c + op[ind].x + op[ind].y);

		if (type = 3)
		{
			int x = qry[ind].ff, y = qry[ind].ss;

			ans[ind] = min(ans[ind], 1ll*(y-x));

			ans[ind] = min(ans[ind], query(1, 1, maxn-1, mp_qry[ind].ff+1, mp_qry[ind].ss-1)-x-y);
		}
	}
}

int main(void)
{
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);

	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d %d", &op[i].x, &op[i].y, &op[i].c);

		mp[op[i].x] = 0;
		mp[op[i].y] = 0;
	}

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &qry[i].ff, &qry[i].ss);

		mp[qry[i].ff] = 0;
		mp[qry[i].ss] = 0;
	}

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	// caching compressed values
	for (int i = 1; i <= n; i++) mp_op[i] = {mp[op[i].x], mp[op[i].y]};
	for (int i = 1; i <= m; i++) mp_qry[i] = {mp[qry[i].ff], mp[qry[i].ss]};

	clear();
	for (int i = 1; i <= m; i++) ans[i] = inf;

	solve(n, m);

	clear();

	for (int i = 1; i <= n; i++)
	{
		swap(op[i].x, op[i].y);
		swap(mp_op[i].ff, mp_op[i].ss);
	}

	for (int i = 1; i <= m; i++)
	{
		swap(qry[i].ff, qry[i].ss);
		swap(mp_qry[i].ff, mp_qry[i].ss);
	}

	solve(n, m);

	for (int i = 1; i <= m; i++)
		printf("%lld\n", ans[i]);
}
