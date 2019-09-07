// infoarena - Regat
// Lúcio Cardoso

// Solution: https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/InfoArena/Regat.cpp

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

typedef long long ll;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n;

int tree[4*maxn], lazy[4*maxn];

int st[maxn], en[maxn], ind[maxn], dist[maxn], tt;

int ans[maxn];

pii back[maxn];

vector<pii> grafo[maxn];

vector<int> query[maxn];

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}

	tree[node] += lazy[node];
	lazy[node] = 0;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = dist[ind[l]];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = max(tree[2*node], tree[2*node+1]);
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

	upd(2*node, l, mid, a, b, v);
	upd(2*node+1, mid+1, r, a, b, v);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

pii get(int node, int l, int r)
{
	flush(node, l, r);

	if (l == r) return {tree[node], l};

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[2*node] >= tree[2*node+1]) return get(2*node, l, mid);
	return get(2*node+1, mid+1, r);
}

void dfs(int u, int p)
{
	st[u] = ++tt;
	ind[tt] = u;

	for (auto pp: grafo[u])
	{
		if (pp.first != p)
		{
			dist[pp.first] = dist[u]+pp.second;
			dfs(pp.first, u);
		}
	}

	en[u] = tt;
}

void dfs2(int u, int p)
{
	for (auto i: query[u])
	{
		pii P = get(1, 1, n);

		ans[i] = P.first;
		back[i] = P;

		upd(1, 1, n, P.second, P.second, -inf);
	}

	for (auto i: query[u])
		upd(1, 1, n, back[i].second, back[i].second, inf);

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p) continue;

		upd(1, 1, n, st[1], en[1], w);
		upd(1, 1, n, st[v], en[v], -2*w);

		dfs2(v, u);

		upd(1, 1, n, st[1], en[1], -w);
		upd(1, 1, n, st[v], en[v], 2*w);
	}
}

int main(void)
{
	freopen("regat.in", "r", stdin);
	freopen("regat.out", "w", stdout);

	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	dfs(1, 0);

	for (int i = 1; i <= m; i++)
	{
		int u;
		scanf("%d", &u);

		query[u].push_back(i);
	}

	build(1, 1, n);

	dfs2(1, 0);

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
