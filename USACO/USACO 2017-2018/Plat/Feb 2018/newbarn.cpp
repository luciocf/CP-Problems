// USACO 2017/2018 - New Barns
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

struct Op
{
	char t;
	int x;
} op[maxn];

int n, q;
int curTime;

int nivel[maxn];
int tab[maxn][20];

int sz[maxn];
int pai[maxn];

int childQtd[maxn];
int childOrd[maxn];

vector<int> tree[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void dfs0(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		tab[v][0] = u, nivel[v] = nivel[u]+1;
		dfs0(v, u);
	}
}

void build(void)
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			tab[i][j] = tab[tab[i][j-1]][j-1];
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	for (int i = 19; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			u = tab[u][i];

	if (u == v) return u;

	for (int i = 19; i >= 0; i--)
		if (tab[u][i] && tab[v][i] && tab[u][i] != tab[v][i])
			u = tab[u][i], v = tab[v][i];

	return tab[u][0];
}

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

void decompose(int u, int p)
{
	dfs(u, 0);

	int c = centroid(u, 0, sz[u]);

	mark[c] = 1, pai[c] = p;

	for (auto v: grafo[c])
		if (!mark[v])
			decompose(v, c);
}

void upd(int node, int l, int r, int pos, int v, int k)
{
	if (l == r)
	{
		tree[k][node] = max(tree[k][node], v);
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v, k);
	else upd(2*node+1, mid+1, r, pos, v, k);

	tree[k][node] = max(tree[k][2*node], tree[k][2*node+1]);
}

int query(int node, int l, int r, int a, int b, int k)
{
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[k][node];

	int mid = (l+r)>>1;

	return max(query(2*node, l, mid, a, b, k), query(2*node+1, mid+1, r, a, b, k));
}

int main(void)
{
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);

	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf(" %c %d", &op[i].t, &op[i].x);

		if (op[i].t == 'B')
		{
			n++;
			int u = op[i].x;

			if (u != -1)
			{
				grafo[u].push_back(n);
				grafo[n].push_back(u);
			}
		}
	}

	for (int i = 1; i <= n; i++)
		if (!nivel[i])
			dfs0(i, 0);

	build();

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			decompose(i, 0);
	
	for (int i = 1; i <= n; i++)
	{
		childQtd[pai[i]]++;
		childOrd[i] = childQtd[pai[i]];
	}

	for (int i = 1; i <= n; i++)
		tree[i].resize(4*childQtd[i]+10);

	for (int i = 1; i <= q; i++)
	{
		if (op[i].t == 'B')
		{
			++curTime;
			int u = curTime, ant = u;

			for (int v = pai[u]; v; v = pai[v])
			{
				int x = nivel[u]+nivel[v]-2*nivel[lca(u, v)];

				upd(1, 1, childQtd[v], childOrd[ant], x, v);
				ant = v;
			}
		}
		else
		{
			int u = op[i].x, ant = u;

			int ans = tree[u][1];

			for (int v = pai[u]; v; v = pai[v])
			{
				if (v <= curTime)
				{
					int x = nivel[u]+nivel[v]-2*nivel[lca(u, v)];

					ans = max(ans, x);

					if (childOrd[ant] != 1)
						ans = max(ans, x+query(1, 1, childQtd[v], 1, childOrd[ant]-1, v));

					if (childOrd[ant] != childQtd[v])
						ans = max(ans, x+query(1, 1, childQtd[v], childOrd[ant]+1, childQtd[v], v));
				}

				ant = v;
			}

			printf("%d\n", ans);
		}
	}
}
