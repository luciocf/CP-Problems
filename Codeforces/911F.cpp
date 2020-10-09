// Codeforces 911F - Tree Destruction
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second	

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5+10;

int grau[maxn];

int pai[maxn], dist[maxn];
pii mx[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pai[v] = u, dist[v] = dist[u]+1;
		dfs(v, u);
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);

		grau[u]++, grau[v]++;
	}

	dfs(1, 0);

	int u = (int)(max_element(dist+1, dist+n+1)-dist);

	dist[u] = 0;
	dfs(u, 0);

	int v = (int)(max_element(dist+1, dist+n+1)-dist);

	for (int i = 1; i <= n; i++)
		mx[i] = {dist[i], u};

	dist[v] = 0, pai[v] = 0;
	dfs(v, 0);

	for (int i = 1; i <= n; i++)
		mx[i] = max(mx[i], {dist[i], v});

	ll tot = 1ll*dist[u]*(dist[u]+1)/2ll;
	vector<pii> leaf, diam;

	while (u)
	{
		if (u != v) diam.push_back({u, v});

		mark[u] = 1;
		u = pai[u];
	}

	queue<int> fila;

	for (int i = 1; i <= n; i++)
	{
		if (!mark[i])
		{
			tot += 1ll*mx[i].ff;

			if (grau[i] == 1) fila.push(i);
		}
	}

	while (!fila.empty())
	{
		int a = fila.front(); fila.pop();

		leaf.push_back({a, mx[a].ss});

		for (auto b: grafo[a])
		{
			if (!mark[b])
			{
				grau[b]--;
				if (grau[b] == 1) fila.push(b);
			}
		}
	}

	printf("%lld\n", tot);
	for (auto pp: leaf)
		printf("%d %d %d\n", pp.ff, pp.ss, pp.ff);
	for (auto pp: diam)
		printf("%d %d %d\n", pp.ff, pp.ss, pp.ff);
}
