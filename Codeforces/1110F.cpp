// Codeforces 1110F - Nearest Leaf
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 5e5+10;
const ll inf = 1e18+10;

struct Query
{
	int l, r, ind;
};

int n, q;

int st[maxn], en[maxn], back[maxn], tt;
ll dist[maxn];

ll ans[maxn];

ll tree[4*maxn], lazy[4*maxn];

vector<pii> grafo[maxn];
vector<Query> query[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt, back[tt] = u;

	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;
		if (v == p) continue;

		dist[v] = dist[u] + 1ll*w;

		dfs(v, u);
	}

	en[u] = tt;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		if (grafo[back[l]].size() == 1) tree[node] = dist[back[l]];
		else tree[node] = inf;

		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
		lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

	tree[node] += lazy[node];
	lazy[node] = 0;
}

void upd(int node, int l, int r, int a, int b, int v)
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

	tree[node] = min(tree[2*node], tree[2*node+1]);
}

ll mn(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return min(mn(2*node, l, mid, a, b), mn(2*node+1, mid+1, r, a, b));
}

void solve(int u, int p)
{
	for (auto Q: query[u])
	{
		int l = Q.l, r = Q.r, ind = Q.ind;

		ans[ind] = mn(1, 1, n, l, r);
	}

	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.second;
		if (v == p) continue;

		upd(1, 1, n, 1, n, w);
		upd(1, 1, n, st[v], en[v], -2*w);

		solve(v, u);

		upd(1, 1, n, 1, n, -w);
		upd(1, 1, n, st[v], en[v], 2*w);
	}
}

int main(void)
{
	scanf("%d %d", &n, &q);

	for (int i = 2; i <= n; i++)
	{
		int p, w;
		scanf("%d %d", &p, &w);

		grafo[i].push_back({p, w});
		grafo[p].push_back({i, w});
	}

	dfs(1, 0);
	build(1, 1, n);

	for (int i = 1; i <= q; i++)
	{
		int u, l, r;
		scanf("%d %d %d", &u, &l, &r);

		query[u].push_back({l, r, i});
	}

	solve(1, 0);

	for (int i = 1; i <= q; i++)
		printf("%lld\n", ans[i]);
}
