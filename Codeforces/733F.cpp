// Codeforces 733F - Drivers Dissatisfaction
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;
const int maxl = 20;

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y];
	}
} dsu;

struct Edge
{
	int u, v, w, c;
	int ind;
} edge[maxn];

int nivel[maxn];
pii tab[maxn][maxl];

int edgePai[maxn];
bool inMst[maxn];

vector<pair<pii, int>> tree[maxn];

bool comp(Edge a, Edge b) {return a.w < b.w;}

void dfs(int u, int p)
{
	for (auto pp: tree[u])
	{
		int v = pp.ff.ff, w = pp.ff.ss;
		if (v == p) continue;

		tab[v][0] = {u, w};
		nivel[v] = nivel[u]+1;

		edgePai[v] = pp.ss;

		dfs(v, u);
	}
}

void build(int n)
{
	for (int j = 1; j < maxl; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			tab[i][j].ff = tab[tab[i][j-1].ff][j-1].ff;
			tab[i][j].ss = max(tab[i][j-1].ss, tab[tab[i][j-1].ff][j-1].ss);
		}
	}
}

int lca(int u, int v)
{
	if (nivel[u] < nivel[v]) swap(u, v);

	int ans = 0;

	for (int i = maxl-1; i >= 0; i--)
		if (nivel[u]-(1<<i) >= nivel[v])
			ans = max(ans, tab[u][i].ss), u = tab[u][i].ff;

	if (u == v) return ans;

	for (int i = maxl-1; i >= 0; i--)
		if (tab[u][i].ff && tab[v][i].ff && tab[u][i].ff != tab[v][i].ff)
			ans = max({ans, tab[u][i].ss, tab[v][i].ss}), u = tab[u][i].ff, v = tab[v][i].ff;

	return max({ans, tab[u][0].ss, tab[v][0].ss});
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
		scanf("%d", &edge[i].w);

	for (int i = 1; i <= m; i++)
		scanf("%d", &edge[i].c);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &edge[i].u, &edge[i].v);
		edge[i].ind = i;
	}

	int S;
	scanf("%d", &S);

	sort(edge+1, edge+m+1, comp);
	dsu.init(n);

	ll mst = 0;

	for (int i = 1; i <= m; i++)
	{
		if (dsu.Find(edge[i].u) != dsu.Find(edge[i].v))
		{
			dsu.Join(edge[i].u, edge[i].v);
			mst += 1ll*edge[i].w;

			tree[edge[i].u].push_back({{edge[i].v, edge[i].w}, i});
			tree[edge[i].v].push_back({{edge[i].u, edge[i].w}, i});

			inMst[i] = 1;
		}
	}

	dfs(1, 0); build(n);

	ll ans = 1e18+10;
	int ind = 1;

	for (int i = 1; i <= m; i++)
	{
		int u = edge[i].u, v = edge[i].v;

		ll cost = mst - 1ll*lca(u, v) + 1ll*edge[i].w - 1ll*S/edge[i].c;

		if (cost < ans)
		{
			ans = cost;
			ind = i;
		}	
	}

	int mx = lca(edge[ind].u, edge[ind].v), ind_mx;

	dfs(edge[ind].u, 0);

	int v = edge[ind].v;
	while (v != edge[ind].u)
	{
		if (tab[v][0].ss == mx)
		{
			ind_mx = edgePai[v];
			break;
		}

		v = tab[v][0].ff;
	}

	printf("%lld\n", ans);

	printf("%d %lld\n", edge[ind].ind, 1ll*edge[ind].w - 1ll*S/edge[ind].c);

	for (int i = 1; i <= m; i++)
	{
		if (i == ind || i == ind_mx) continue;

		if (inMst[i]) printf("%d %d\n", edge[i].ind, edge[i].w);
	}
}
