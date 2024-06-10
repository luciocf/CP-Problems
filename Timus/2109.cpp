// Timus 2109 - Tourism on Mars
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+1;
const int maxl = 21;

vector<int> grafo[maxn];

int n;

struct BinaryLifting
{
	int tab[maxn][maxl], nivel[maxn];

	void dfs(int u, int p)
	{
		for (auto v: grafo[u])
		{
			if (v != p)
			{
				tab[v][0] = u, nivel[v] = nivel[u]+1;
				dfs(v, u);
			}
		}
	}

	void calc(void)
	{
		memset(tab, -1, sizeof tab);
		dfs(1, 0);

		for (int j = 1; j < maxl; j++)
			for (int i = 1; i <= n; i++)
				tab[i][j] = tab[tab[i][j-1]][j-1];
	}

	int lca(int u, int v)
	{
		if (nivel[u] < nivel[v]) swap(u, v);

		for (int i = maxl-1; i >= 0; i--)
			if (nivel[u]-(1<<i) >= nivel[v])
				u = tab[u][i];

		if (u == v) return u;

		for (int i = maxl-1; i >= 0; i--)
			if (tab[u][i] != -1 and tab[v][i] != -1 and tab[u][i] != tab[v][i])
				u = tab[u][i], v = tab[v][i];

		return tab[u][0];
	}
} LCA;

struct SegmentTree
{
	int tree[4*maxn];

	void build(int node, int l, int r)
	{
		if (l > r) return;

		if (l == r)
		{
			tree[node] = LCA.lca(l, l+1);
			return;
		}

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);

		int u = tree[2*node], v = tree[2*node+1];
		if (u == maxn) tree[node] = v;
		else if (v == maxn) tree[node] = u;
		else if (LCA.nivel[u] < LCA.nivel[v]) tree[node] = u;
		else tree[node] = v;
	}

	int query(int node, int l, int r, int a, int b)
	{
		if (l > b || r < a) return maxn;
		if (l >= a and r <= b) return tree[node];

		int mid = (l+r)>>1;

		int u = query(2*node, l, mid, a, b), v = query(2*node+1, mid+1, r, a, b);
		if (u == maxn) return v;
		else if (v == maxn) return u;
		else if (LCA.nivel[u] < LCA.nivel[v]) return u;
		return v;
	}
} seg;

int Query(int l, int r)
{
	if (l == r) return l;
	return seg.query(1, 1, n-1, l, r-1);
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

	LCA.calc();
	seg.build(1, 1, n-1);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		printf("%d\n", Query(l, r));
	}
}
