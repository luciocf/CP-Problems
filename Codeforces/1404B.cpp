// Codeforces 1404B - Tree Tag
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int dist[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dist[v] = dist[u]+1;
		dfs(v, u);
	}
}

void solve(void)
{
	int n, a, b, da, db;
	scanf("%d %d %d %d %d", &n, &a, &b, &da, &db);

	for (int i = 1; i <= n; i++)
		grafo[i].clear();

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dist[a] = 0;
	dfs(a, 0);

	if (dist[b] <= da)
	{
		printf("Alice\n");
		return;
	}

	int u = max_element(dist+1, dist+n+1)-dist;

	dist[u] = 0;
	dfs(u, 0);

	int diam = *max_element(dist+1, dist+n+1);

	if (da >= (diam+1)/2)
	{
		printf("Alice\n");
		return;
	}

	if (db > 2*da) printf("Bob\n");
	else printf("Alice\n");
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--) solve();
}
