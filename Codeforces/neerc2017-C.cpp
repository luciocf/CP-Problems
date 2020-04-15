// NEERC 2017 - C - Connections
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int in[maxn], tt;
int tot;

bool mark[maxn];

pii edge[maxn];

vector<pii> grafo[maxn];

void dfs(int u)
{
	in[u] = ++tt;
	int mn = maxn, ind = -1;

	for (auto E: grafo[u])
	{
		int v = E.first, e = E.second;

		if (in[v])
		{
			if (in[v] < mn)
				mn = in[v], ind = e;
			continue;
		}

		mark[e] = 1, ++tot;
		dfs(v);
	}

	if (ind != -1)
		mark[ind] = 1, ++tot;
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n, m;
		scanf("%d %d", &n, &m);

		tt = 0, tot = 0;
		for (int i = 1; i <= n; i++)
			grafo[i].clear(), in[i] = 0;
		for (int i = 1; i <= m; i++)
			mark[i] = 0;

		for (int i = 1; i <= m; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			edge[i] = {u, v};
			grafo[u].push_back({v, i});
		}

		dfs(1);

		for (int i = 1; i <= m; i++)
		{
			if (!mark[i] && tot < 2*n)
				++tot;
			else if (!mark[i] && tot == 2*n)
				printf("%d %d\n", edge[i].first, edge[i].second);
		}
	}
}
