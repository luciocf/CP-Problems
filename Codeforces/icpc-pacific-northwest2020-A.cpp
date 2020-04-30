// ICPC Pacific Northwest 2020 Regional D1 - A - Radio Prize
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e5+10;

int n, soma_tot;
int a[maxn];

int sz[maxn], soma[maxn];
ll sub1[maxn], sub2[maxn];

ll ans[maxn];

vector<pii> grafo[maxn];

void dfs(int u, int p, int d)
{
	sz[u] = 1, soma[u] = a[u];

	sub1[1] += 1ll*d, sub2[1] += 1ll*d*a[u]; 

	for (auto e: grafo[u])
	{
		int v = e.first, w = e.second;
		if (v == p) continue;

		dfs(v, u, d+w);

		sz[u] += sz[v], soma[u] += soma[v];
	}
}

void solve(int u, int p)
{
	ans[u] = 1ll*a[u]*sub1[u] + sub2[u];

	for (auto e: grafo[u])
	{
		int v = e.first, w = e.second;
		if (v == p) continue;

		sub1[v] = sub1[u] + 1ll*w*(n - 2*sz[v]);
		sub2[v] = sub2[u] + 1ll*w*(soma_tot - 2*soma[v]);

		solve(v, u);
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		soma_tot += a[i];
	}

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	dfs(1, 0, 0);
	solve(1, 0);

	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
}
