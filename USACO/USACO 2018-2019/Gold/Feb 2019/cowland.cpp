// USACO Gold Feb 2019 - Cow Land
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int a[maxn];

int sz[maxn], nivel[maxn], pai[maxn];
int chain[maxn], head[maxn], pos[maxn], val[maxn], cc=1, pp;

int tree[4*maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1, pai[v] = u;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

void hld(int u, int p)
{
	if (!head[cc]) head[cc] = u;
	
	chain[u] = cc, pos[u] = ++pp;
	val[pos[u]] = a[u];

	int maior = -1, ind = -1;
	for (auto v: grafo[u])
		if (v != p && sz[v] > maior)
			maior = sz[v], ind = v;

	if (ind != -1)
		hld(ind, u);

	for (auto v: grafo[u])
		if (v != p && v != ind)
			++cc, hld(v, u);
}

int lca(int u, int v)
{
	while (chain[u] != chain[v])
	{
		if (nivel[head[chain[u]]] > nivel[head[chain[v]]])
			u = pai[head[chain[u]]];
		else
			v = pai[head[chain[v]]];
	}

	return (nivel[u] > nivel[v] ? v : u);
}

void build(int node, int l, int r)
{
	if(l == r)
	{
		tree[node] = val[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = tree[2*node]^tree[2*node+1];
}

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node] = v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid)
		upd(2*node, l, mid, pos, v);
	else
		upd(2*node+1, mid+1, r, pos, v);

	tree[node] = tree[2*node]^tree[2*node+1];
}

int query(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node];

	int mid = (l+r)>>1;

	return query(2*node, l, mid, a, b)^query(2*node+1, mid+1, r, a, b);
}

void updPath(int u, int v)
{
	a[u] = v, val[pos[u]] = v;
	upd(1, 1, n, pos[u], v);
}

int queryPath(int u, int v)
{
	int ans = 0;
	while (true)
	{
		if (chain[u] == chain[v])
			return (ans ^ query(1, 1, n, pos[v], pos[u]));

		ans ^= query(1, 1, n, pos[head[chain[u]]], pos[u]);
		u = pai[head[chain[u]]];
	}
	printf("\n");

	return ans;
}

int main(void)
{
	FILE *fin = fopen("cowland.in", "r");
	FILE *fout = fopen("cowland.out", "w");

	int q;
	fscanf(fin, "%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		fscanf(fin, "%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0); hld(1, 0);
	build(1, 1, n);

	for (int i = 1; i <= q; i++)
	{
		int op, u, v;
		fscanf(fin, "%d %d %d", &op, &u, &v);

		if (op == 1)
		{
			updPath(u, v);
		}
		else
		{
			int l = lca(u, v);
			fprintf(fout, "%d\n", queryPath(u, l)^queryPath(v, l)^a[l]);
		}
	}
}
