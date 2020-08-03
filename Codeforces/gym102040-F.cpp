// Codeforces - 2018-2019 ACM-ICPC, Asia Dhaka Regional Contest - F
// Lúcio Cardoso

// Solution: use HLD and a Lazy Segment tree. Answer for k updates is freq. of the maximum element if it's
// equal to k, otherwise 0.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e4+10;

int n;

vector<int> grafo[maxn];

struct SegmentTree
{
	pii tree[4*maxn];
	int lazy[4*maxn];

	void build(int node, int l, int r)
	{
		tree[node] = {0, r-l+1};
		lazy[node] = 0;

		if (l == r) return;

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r) lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

		tree[node].ff += lazy[node];
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

		tree[node].ff = max(tree[2*node].ff, tree[2*node+1].ff);
		tree[node].ss = 0;

		if (tree[node].ff == tree[2*node].ff) tree[node].ss += tree[2*node].ss;
		if (tree[node].ff == tree[2*node+1].ff) tree[node].ss += tree[2*node+1].ss;
	}
} seg;

struct HeavyLight
{
	int pai[maxn], nivel[maxn], sz[maxn];
	int chain[maxn], cc;
	int head[maxn];
	int pos[maxn], tt;

	void init(void)
	{
		cc = 1, tt = 0;
		memset(head, 0, sizeof head);
	}

	void dfs(int u, int p)
	{
		sz[u] = 1;

		for (auto v: grafo[u])
		{
			if (v == p) continue;

			pai[v] = u, nivel[v] = nivel[u]+1;
			dfs(v, u);
			sz[u] += sz[v];
		}
	}

	void hld(int u)
	{
		if (!head[cc]) head[cc] = u;

		chain[u] = cc;
		pos[u] = ++tt;

		int mx = 0, ind = 0;
		for (auto v: grafo[u])
			if (v != pai[u] && sz[v] > mx)
				mx = sz[v], ind = v;

		if (ind) hld(ind);

		for (auto v: grafo[u])
			if (v != pai[u] && v != ind)
				++cc, hld(v);
	}

	int lca(int u, int v)
	{
		while (chain[u] != chain[v])
		{
			if (nivel[head[chain[u]]] > nivel[head[chain[v]]]) u = pai[head[chain[u]]];
			else v = pai[head[chain[v]]];
		}

		return (nivel[u] > nivel[v] ? v : u);
	}

	void updPath(int u, int v, int x)
	{
		while (true)
		{
			if (chain[u] == chain[v])
			{
				seg.upd(1, 1, n, pos[v], pos[u], x);
				return;
			}

			seg.upd(1, 1, n, pos[head[chain[u]]], pos[u], x);
			u = pai[head[chain[u]]];
		}
	}
} HLD;

void solve(int tc)
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		grafo[i].clear();

	HLD.init();

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	HLD.dfs(1, 0);
	HLD.hld(1);

	int q;
	cin >> q;

	cout << "Case " << tc << ":\n";
	while (q--)
	{
		seg.build(1, 1, n);

		int k;
		cin >> k;

		int ans = 0;

		for (int i = 1; i <= k; i++)
		{
			int u, v;
			cin >> u >> v;

			int l = HLD.lca(u, v);

			HLD.updPath(u, l, 1); HLD.updPath(v, l, 1); HLD.updPath(l, l, -1);
		}

		seg.flush(1, 1, n);

		if (seg.tree[1].ff == k) cout << seg.tree[1].ss << "\n";
		else cout << "0\n";
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int tc;
	cin >> tc;

	for (int i = 1; i <= tc; i++) solve(i);
}
