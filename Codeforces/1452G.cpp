// Codeforces 1452G - Game On Tree
// Lúcio Cardoso

// Solution is the same as the one in editorial (using a segment tree for queries)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5+10;

int n;

bool chip[maxn];
int dist[maxn];

int ans[maxn];

vector<int> grafo[maxn];

void bfs(void)
{
	queue<int> fila;

	for (int i = 1; i <= n; i++)
	{
		if (chip[i])
		{
			dist[i] = 0;
			fila.push(i);
		}
	}

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[v] == -1)
			{
				dist[v] = dist[u]+1;
				fila.push(v);
			}
		}
	}
}

struct SegmentTree
{
	int tree[4*maxn];

	void upd(int node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			tree[node] = v;
			return;
		}

		int mid = (l+r)>>1;

		if (pos <= mid) upd(2*node, l, mid, pos, v);
		else upd(2*node+1, mid+1, r, pos, v);

		tree[node] = max(tree[2*node], tree[2*node+1]);
	}

	int get(int node, int l, int r, int v)
	{
		if (tree[node] <= v) return -1;
		if (l == r) return l;

		int mid = (l+r)>>1;

		if (tree[2*node+1] > v) return get(2*node+1, mid+1, r, v);
		return get(2*node, l, mid, v);
	}
} seg;

struct Centroid
{
	int sz[maxn];
	bool mark[maxn];

	multiset<int> st[maxn];

	void dfs(int u, int p)
	{
		sz[u] = 1;

		for (auto v: grafo[u])
		{
			if (v == p || mark[v]) continue;

			dfs(v, u);

			sz[u] += sz[v];
		}
	}

	int centroid(int u, int p, int S)
	{
		for (auto v: grafo[u])
			if (v != p && !mark[v] && sz[v] > S/2)
				return centroid(v, u, S);

		return u;
	}

	void upd(int u, int p, int d, bool add)
	{
		if (dist[u] >= d)
		{
			if (add) st[dist[u]].insert(dist[u]-d);
			else st[dist[u]].erase(st[dist[u]].find(dist[u]-d));

			if (st[dist[u]].size() == 0) seg.upd(1, 0, n, dist[u], 0);
			else seg.upd(1, 0, n, dist[u], *st[dist[u]].rbegin());
		}

		for (auto v: grafo[u])
		{
			if (v == p || mark[v]) continue;

			upd(v, u, d+1, add);
		}
	}

	void get(int u, int p, int d)
	{
		if (!chip[u]) ans[u] = max(ans[u], seg.get(1, 0, n, d));

		for (auto v: grafo[u])
		{
			if (v == p || mark[v]) continue;

			get(v, u, d+1);
		}
	}

	void decompose(int u)
	{
		dfs(u, 0);

		int c = centroid(u, 0, sz[u]);
		mark[c] = 1;

		st[dist[c]].insert(dist[c]);
		seg.upd(1, 0, n, dist[c], dist[c]);

		for (auto v: grafo[c])
		{
			if (mark[v]) continue;

			get(v, c, 1);
			upd(v, c, 1, 1);
		}

		if (!chip[c]) ans[c] = max(ans[c], seg.get(1, 0, n, 0));

		for (auto v: grafo[c])
		{
			if (mark[v]) continue;

			upd(v, c, 1, 0);
			get(v, c, 1);
		}

		st[dist[c]].erase(st[dist[c]].find(dist[c]));
		seg.upd(1, 0, n, dist[c], 0);

		for (auto v: grafo[c])
			if (!mark[v])
				decompose(v);
	}
} CD;

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

	int k;
	scanf("%d", &k);

	while (k--)
	{
		int u;
		scanf("%d", &u);

		chip[u] = 1;
	}

	memset(dist, -1, sizeof dist);
	bfs();

	CD.decompose(1);

	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
