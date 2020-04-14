// Codeforces 893F - Subtree Minimum Query
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 1e9+10;

vector<pii> tree[4*maxn];

int n;
int a[maxn];

int st[maxn], en[maxn], back[maxn], tt;
int nivel[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt;
	back[tt] = u;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		dfs(v, u);
	}

	en[u] = tt;
}

void join(int node, int l, int r)
{
	int ptr_l = 0, ptr_r = 0;

	while (ptr_l < tree[2*node].size() || ptr_r < tree[2*node+1].size())
	{
		if (ptr_l == tree[2*node].size() ||
		   (ptr_r != tree[2*node+1].size() && tree[2*node+1][ptr_r].first < tree[2*node][ptr_l].first))
		{
			int x = tree[2*node+1][ptr_r].first;
			int y = tree[2*node+1][ptr_r].second;
			if (tree[node].size()) y = min(y, tree[node].back().second);

			tree[node].push_back({x, y});

			ptr_r++;
		}
		else
		{
			int x = tree[2*node][ptr_l].first;
			int y = tree[2*node][ptr_l].second;
			if (tree[node].size()) y = min(y, tree[node].back().second);

			tree[node].push_back({x, y});

			ptr_l++;
		}
	}
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].push_back({nivel[back[l]], a[back[l]]});
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	join(node, l, r);
}

int query(int node, int l, int r, int a, int b, int v)
{
	if (l > b || r < a) return inf;

	if (l >= a && r <= b)
	{
		if (tree[node][0].first > v) return inf;

		auto it = upper_bound(tree[node].begin(), tree[node].end(), make_pair(v, inf));
		it--;

		return it->second;
	}

	int mid = (l+r)>>1;

	return min(query(2*node, l, mid, a, b, v), query(2*node+1, mid+1, r, a, b, v));
}

int main(void)
{
	int root;
	scanf("%d %d", &n, &root);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(root, 0);
	build(1, 1, n);

	int q;
	scanf("%d", &q);
	int last = 0;

	while (q--)
	{
		int u, k;
		scanf("%d %d", &u, &k);

		u = (u+last)%n + 1, k = (k+last)%n;

		last = query(1, 1, n, st[u], en[u], nivel[u]+k);
		printf("%d\n", last);
	}
}
