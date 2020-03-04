// CF 1282E - The Cake Is a Lie
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

map<tuple<int, int, int>, int> mp;

bool mark[maxn];

set<int> grafo[maxn], g_aux[maxn];

vector<int> ciclo[maxn], P;
vector<pii> Q;

void init(int n)
{
	memset(mark, 0, sizeof mark);
	mp.clear(), P.clear(), Q.clear();
	for (int i = 1; i <= n; i++)
	{
		grafo[i].clear(), g_aux[i].clear();
		ciclo[i].clear();
	}
}

int get_triangle(int a, int b, int c)
{
	if (mp[{a, b, c}]) return mp[{a, b, c}];
	if (mp[{a, c, b}]) return mp[{a, c, b}];
	if (mp[{b, a, c}]) return mp[{b, a, c}];
	if (mp[{b, c, a}]) return mp[{b, c, a}];
	if (mp[{c, a, b}]) return mp[{c, a, b}];
	return mp[{c, b, a}];
}

void dfs(int u)
{
	mark[u] = 1;
	P.push_back(u);

	for (auto v: ciclo[u])
		if (!mark[v])
			dfs(v);
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n;
		scanf("%d", &n);

		init(n);

		for (int i = 1; i <= n-2; i++)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);

			mp[{a, b, c}] = i;

			grafo[a].insert(b), grafo[a].insert(c);
			grafo[b].insert(a), grafo[b].insert(c);
			grafo[c].insert(b), grafo[c].insert(a);

			g_aux[a].insert(b), g_aux[a].insert(c);
			g_aux[b].insert(a), g_aux[b].insert(c);
			g_aux[c].insert(b), g_aux[c].insert(a);
		}

		queue<int> fila;

		for (int i = 1; i <= n; i++)
			if (grafo[i].size() == 2)
				fila.push(i);

		while (!fila.empty())
		{
			int a = fila.front(); fila.pop();

			if (g_aux[a].size() != 2)
			{
				if (g_aux[a].size() == 1)
				{
					int b = *g_aux[a].begin();

					if (g_aux[b].find(a) != g_aux[b].end())
						g_aux[b].erase(a);
				}

				continue;
			}
			
			int b = *g_aux[a].begin(); g_aux[a].erase(b);
			int c = *g_aux[a].begin();

			if (g_aux[b].find(a) != g_aux[b].end())
						g_aux[b].erase(a);

			if (g_aux[c].find(a) != g_aux[c].end())
						g_aux[c].erase(a);

			Q.push_back({get_triangle(a, b, c), a});

			if (g_aux[b].size() == 2) fila.push(b);
			if (g_aux[c].size() == 2) fila.push(c);
		}

		map<pii, int> edge;

		for (auto pp: Q)
		{
			int u = pp.second;

			if (grafo[u].size() == 2)
			{
				int a = *grafo[u].begin(); grafo[u].erase(a);
				int b = *grafo[u].begin();

				if (!edge[{u, a}])
				{
					ciclo[u].push_back(a);
					ciclo[a].push_back(u);
				}

				if (!edge[{u, b}])
				{
					ciclo[u].push_back(b);
					ciclo[b].push_back(u);
				}

				edge[{a, b}] = edge[{b, a}] = 1;

				if (grafo[a].find(u) != grafo[a].end())
					grafo[a].erase(u);

				if (grafo[b].find(u) != grafo[b].end())
					grafo[b].erase(u);
			}
		}

		dfs(1);

		for (auto p: P)
			printf("%d ", p);
		printf("\n");
		for (auto q: Q)
			printf("%d ", q.first);
		printf("\n");
	}
}
