// CEOI 2015 - Pipes
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e5+10;
 
struct DSU
{
	int pai[maxn];
 
	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i;
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
 
		pai[y] = x;
	}
} dsu;

struct DSU2
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
} dsu2;
 
pii edge[maxn], old[maxn];
 
void walk(int u, int v)
{
	vector<int> path_u, path_v;
 
	while (true)
	{
		path_u.push_back(u);
 
		if (!edge[u].ss) break;
		u = dsu.Find(edge[u].ss);
	}
 
	while (true)
	{
		path_v.push_back(v);
 
		if (!edge[v].ss) break;
		v = dsu.Find(edge[v].ss);
	}
 
	int lca, ptr_u = path_u.size()-1, ptr_v = path_v.size()-1;
 
	while (ptr_u >= 0 && ptr_v >= 0 && path_u[ptr_u] == path_v[ptr_v])
	{
		lca = path_u[ptr_u];
		ptr_u--, ptr_v--;
	}
 
	pii pp = edge[lca];
	edge[lca] = {0, 0};
 
	for (int i = 0; i <= ptr_u; i++)
	{
		edge[path_u[i]] = {0, 0};
		dsu.Join(path_u[i], lca);
	}
 
	for (int i = 0; i <= ptr_v; i++)
	{
		edge[path_v[i]] = {0, 0};
		dsu.Join(path_v[i], lca);
	}
 
	edge[dsu.Find(lca)] = pp;
}
 
void makeroot(int u)
{
	bool end = 0;
	if (edge[u].ss == 0) return;
 
	old[u] = edge[u];
 
	while (!end)
	{
		int next_u = dsu.Find(old[u].ss);
		end |= (!edge[next_u].ss);
 
		old[next_u] = edge[next_u];
		edge[next_u] = {old[u].ss, old[u].ff};
 
		u = next_u;
	}
}
 
int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
 
	dsu.init(n); dsu2.init(n);
 
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
 
		int fu = dsu.Find(u), fv = dsu.Find(v);
 
		if (fu == fv) continue;
 
		if (dsu2.Find(fu) == dsu2.Find(fv))	walk(fu, fv);
		else
		{
			int cu = dsu2.Find(fu), cv = dsu2.Find(fv);
 
			if (dsu2.peso[cu] > dsu2.peso[cv])
			{
				makeroot(fv);
				edge[fv] = {v, u};
			}
			else
			{
				makeroot(fu);
				edge[fu] = {u, v};
			}
 
			dsu2.Join(fu, fv);
		}
	}
 
	for (int i = 1; i <= n; i++)
		if (edge[i].ff)
			printf("%d %d\n", edge[i].ff, edge[i].ss);
}
