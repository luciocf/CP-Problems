// USACO 2017-2018 - Promotion Counting
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int a[maxn];

int in[maxn], out[maxn], w[maxn], tt;

vector<int> grafo[maxn];

vector<int> tree[4*maxn];

void dfs(int u, int p)
{
	in[u] = ++tt;
	w[tt] = a[u];

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	out[u] = tt;
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].push_back(w[l]);
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), back_inserter(tree[node]));
}

int query(int node, int l, int r, int a, int b, int x)
{
	if (l > b || r < a) return 0;

	if (l >= a && r <= b)
		return (int)(tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), x));

	int mid = (l+r)>>1;

	return query(2*node, l, mid, a, b, x)+query(2*node+1, mid+1, r, a, b, x);
}

int main(void)
{
	freopen("promote.in", "r", stdin);
	freopen("promote.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		grafo[i].push_back(p);
		grafo[p].push_back(i);
	}

	dfs(1, 0);
	build(1, 1, n);

	for (int i = 1; i <= n; i++)
		printf("%d\n", query(1, 1, n, in[i], out[i], a[i]));
}
