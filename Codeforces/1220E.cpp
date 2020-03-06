// Codeforces 1220E - Tourism
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5+10;

int a[maxn];

int in[maxn], low[maxn], tt;

int comp[maxn];
ll soma[maxn];

ll sub1[maxn], sub2[maxn];
int sz[maxn];

bool back[maxn];

bool bridge[maxn];

vector<pii> grafo[maxn];
vector<int> tree[maxn];

void find_bridge(int u, int p)
{
	in[u] = low[u] = ++tt;

	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;

		if (in[v])
		{
			if (v != p) low[u] = min(low[u], in[v]);
			continue;
		}

		find_bridge(v, u);

		if (low[v] > in[u]) bridge[e] = 1;

		low[u] = min(low[u], low[v]);
	}
}

void dfs(int u, int cc)
{
	comp[u] = cc;
	soma[cc] += 1ll*a[u], sz[cc]++;

	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;
		if (comp[v] || bridge[e]) continue;

		dfs(v, cc);
	}
}

void calc(int u, int p)
{
	sub1[u] = sub2[u] = soma[u];

	if (sz[u] > 1) back[u] = 1;

	for (auto v: tree[u])
	{
		if (v != p)
		{
			calc(v, u);

			if (back[v])
			{
				back[u] = 1;
				sub1[u] += sub1[v], sub2[u] += sub1[v];
			}
		}
	}

	ll mx = sub2[u];

	for (auto v: tree[u])
	{
		if (v != p)
		{
			if (!back[v]) mx = max(mx, sub2[u]+sub2[v]);
			else mx = max(mx, sub2[u] - sub1[v] + sub2[v]);
		}
	}

	sub2[u] = mx;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});
	}

	int S;
	scanf("%d", &S);

	find_bridge(S, 0);

	int cc = 0;
	for (int u = 1; u <= n; u++)
		if (!comp[u])
			dfs(u, ++cc);

	for (int u = 1; u <= n; u++)
		for (auto v: grafo[u])
			if (comp[u] != comp[v.first])
				tree[comp[u]].push_back(comp[v.first]);

	calc(comp[S], 0);

	printf("%lld\n", max(sub1[comp[S]], sub2[comp[S]]));
}
