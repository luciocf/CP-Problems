// CEOI 2020 - Spring Cleaning
// Lúcio Cardoso

// Solution is the same as in editorial (with HLD)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n, q;

vector<int> grafo[maxn];

struct SegmentTree
{
	int tree[2][4*maxn], lazy[4*maxn];

	void build(int node, int l, int r)
	{
		tree[0][node] = r-l+1;
		if (l == r) return;

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}

	void flush(int node, int l, int r)
	{
		if (!lazy[node]) return;

		if (l != r) lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

		if (abs(lazy[node])%2) swap(tree[0][node], tree[1][node]);

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

		tree[0][node] = tree[0][2*node]+tree[0][2*node+1];
		tree[1][node] = tree[1][2*node]+tree[1][2*node+1];
	}
} seg;

struct HeavyLight
{
	int pai[maxn], nivel[maxn], sub[maxn];
	int head[maxn], chain[maxn], pos[maxn], cc, tt;

	void init(void)
	{
		cc = 1;
	}

	void dfs(int u, int p)
	{
		sub[u] = 1;
		for (auto v: grafo[u])
		{
			if (v == p) continue;

			pai[v] = u, nivel[v] = nivel[u]+1;
			dfs(v, u);
			sub[u] += sub[v];
		}
	}

	void hld(int u)
	{
		if (!head[cc]) head[cc] = u;
		chain[u] = cc, pos[u] = ++tt;

		int mx = 0, ind = -1;
		for (auto v: grafo[u])
			if (v != pai[u] && sub[v] > mx)
				mx = sub[v], ind = v;

		if (ind != -1) hld(ind);

		for (auto v: grafo[u])
		{
			if (v != pai[u] && v != ind)
			{
				++cc;
				hld(v);
			}
		}
	}

	void upd_path(int u, int v, int k)
	{
		while (true)
		{
			if (chain[u] == chain[v])
			{
				seg.upd(1, 1, n, pos[v], pos[u], k);
				return;
			}

			seg.upd(1, 1, n, pos[head[chain[u]]], pos[u], k);
			u = pai[head[chain[u]]];
		}
	}
} HLD;

int liga[maxn];

int main(void)
{
	scanf("%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	int r;
	for (int i = 1; i <= n; i++)
		if (grafo[i].size() != 1)
			r = i;


	seg.build(1, 1, n);
	HLD.init(); HLD.dfs(r, 0); HLD.hld(r);

	for (int i = 1; i <= n; i++)
		if (grafo[i].size() == 1)
			HLD.upd_path(i, r, 1);


	int leaf = 0;
	for (int i = 1; i <= n; i++)
		if (grafo[i].size() == 1)
			leaf++;

	while (q--)
	{
		int d;
		scanf("%d", &d);

		int l = leaf+d;

		vector<int> A;
		set<int> B;

		for (int i = 1; i <= d; i++)
		{
			int u;
			scanf("%d", &u);

			liga[d] = u;

			HLD.upd_path(u, r, 1);

			A.push_back(u);
			B.insert(u);
		}

		for (auto v: B)
		{
			if (grafo[v].size() == 1)
			{
				l--;
				HLD.upd_path(v, r, -1);
			}
		}

		int ans = n+d-1;
		seg.flush(1, 1, n);
		ans += seg.tree[0][1]-1;

		if (l%2) printf("-1\n");
		else printf("%d\n", ans);

		for (auto v: B)
			if (grafo[v].size() == 1)
				HLD.upd_path(v, r, 1);

		for (auto v: A)
			HLD.upd_path(v, r, -1);
	}
}
