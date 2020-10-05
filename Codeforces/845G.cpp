// Codeforces 845G - Shortest Path Problem?
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

struct Edge
{
	int v, w, ind;
};

int nivel[maxn], dist[maxn];
bool mark[maxn];

vector<int> ciclo;

int b[maxn];

vector<Edge> grafo[maxn];

void dfs(int u, int e)
{
	mark[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.v, w = pp.w, ind = pp.ind;

		if (mark[v])
		{
			if (ind != e && nivel[v] < nivel[u])
				ciclo.push_back(dist[u]^dist[v]^w);

			continue;
		}

		nivel[v] = nivel[u]+1, dist[v] = dist[u]^w;
		dfs(v, ind);
	}
}

void add(int v)
{
	for (int i = 28; i >= 0; i--)
	{
		if (!(v&(1<<i))) continue;

		if (!b[i])
		{
			b[i] = v;
			return;
		}

		v ^= b[i];
	}
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		if (u == v) ciclo.push_back(w);
		else
		{
			grafo[u].push_back({v, w, i});
			grafo[v].push_back({u, w, i});
		}
	}

	dfs(1, 0);

	for (auto v: ciclo)
		add(v);

	int ans = dist[n];

	for (int i = 28; i >= 0; i--)
		if (ans&(1<<i))
			ans ^= b[i];

	printf("%d\n", ans);
}
