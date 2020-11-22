// Codeforces 708C - Centroids
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e5+10;

struct FenwickTree
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] += v;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans += bit[x];
		return ans;
	}

	int get(int l, int r)
	{
		return soma(r) - soma(l-1);
	}
} BIT;

int st[maxn], en[maxn], back[maxn], tt;
int sz[maxn];

struct MergeSortTree
{
	vector<int> tree[4*maxn];

	void build(int node, int l, int r)
	{
		if (l == r)
		{
			tree[node].push_back(sz[back[l]]);
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		int a = 2*node, b = 2*node+1;

		merge(tree[a].begin(), tree[a].end(), tree[b].begin(), tree[b].end(), back_inserter(tree[node]));
	}

	int query(int node, int l, int r, int a, int b, int k1, int k2)
	{
		if (l > b || r < a) return 0;

		if (l >= a && r <= b)
		{
			int v2 = (int)(upper_bound(tree[node].begin(), tree[node].end(), k2)-tree[node].begin());
			int v1 = (int)(upper_bound(tree[node].begin(), tree[node].end(), k1-1)-tree[node].begin());

			return v2-v1;
		}

		int mid = (l+r)>>1;

		return query(2*node, l, mid, a, b, k1, k2) + query(2*node+1, mid+1, r, a, b, k1, k2);
	}
} seg;

int n;

bool ans[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt, back[tt] = u;
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		sz[u] += sz[v];
	}

	en[u] = tt;
}

int centroid(int u, int p)
{
	for (auto v: grafo[u])
		if (v != p && sz[v] > n/2)
			return centroid(v, u);

	return u;
}

void solve(int u, int p, bool tem)
{
	int l = (n-sz[u])-n/2, r = n/2;

	if (n-sz[u] <= n/2 || tem) 
		ans[u] = 1;
	else if (seg.query(1, 1, n, 1, n, l, r) > seg.query(1, 1, n, st[u], en[u], l, r) + BIT.get(l, r))
		ans[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		BIT.upd(sz[u], 1);

		solve(v, u, (tem || (sz[u] == n/2)) && (n%2 == 0));

		BIT.upd(sz[u], -1);
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);

	int c = centroid(1, 0);

	tt = 0;
	dfs(c, 0);

	seg.build(1, 1, n);

	solve(c, 0, 0);

	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
