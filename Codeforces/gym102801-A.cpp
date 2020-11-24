// The 14th Chinese Northeast Collegiate Programming Contest - A - Micro Structure Thread
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

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

int n;
int a[maxn];

int dist[maxn], source[maxn];

vector<int> grafo[maxn], tree[maxn];

int pai[maxn], perm[maxn], tt;

void bfs(void)
{
	queue<int> fila;

	for (int i = 1; i <= n; i++)
	{
		dist[a[i]] = 0, source[a[i]] = i;
		fila.push(a[i]);
	}

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[v] == -1)
			{
				dist[v] = dist[u]+1;
				source[v] = source[u];

				fila.push(v);
			}
		}
	}
}

void dfs(int u, int p)
{
	perm[++tt] = u;

	for (auto v: tree[u])
	{
		if (v == p) continue;

		pai[v] = u;
		dfs(v, u);
	}
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		for (int i = 0; i < (1<<18); i++)
			grafo[i].clear();

		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
		{
			tree[i].clear();

			scanf("%d", &a[i]);
		}

		for (int i = 0; i < (1<<18); i++)
			for (int j = 0; j < 18; j++)
				grafo[i].push_back(i^(1<<j));

		memset(dist, -1, sizeof dist);
		bfs();

		vector<pair<int, pii>> edges;

		for (int i = 0; i < (1<<18); i++)
			for (auto j: grafo[i])
				if (source[i] != source[j])
					edges.push_back({dist[i] + dist[j] + 1, {source[i], source[j]}});

		dsu.init(n);
		sort(edges.begin(), edges.end());

		int ans = 0;

		for (auto e: edges)
		{
			if (dsu.Find(e.ss.ff) != dsu.Find(e.ss.ss))
			{
				dsu.Join(e.ss.ff, e.ss.ss);
				ans += e.ff;

				tree[e.ss.ff].push_back(e.ss.ss);
				tree[e.ss.ss].push_back(e.ss.ff);
			}
		}

		printf("%d\n", ans);

		tt = 0;
		dfs(1, 0);

		pai[1] = n;

		for (int i = 1; i <= n; i++)
			printf("%d ", perm[i]);
		printf("\n");
		for (int i = 1; i <= n; i++)
			printf("%d ", pai[perm[i]]);
		printf("\n");
	}
}
