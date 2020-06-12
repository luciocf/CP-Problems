// ICPC Swiss Subregional 2019 - J - Seating Pairs
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int sz[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void dfs(int u)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (sz[v] > 0) continue;

		dfs(v);

		sz[u] += sz[v];
	}
}

void dfs2(int u)
{
	mark[u] = true;
	vector<int> V;

	for (auto v: grafo[u])
	{ 
		if (mark[v]) continue;

		dfs2(v);

		if (sz[v] % 2)
			V.push_back(v);
	}

	if (V.size() == 0) return;

	int i;

	for (i = 1; i < V.size(); i += 2)
		printf("%d %d %d\n", V[i-1], V[i], u);

	if (i != V.size() + 1)
		printf("%d %d -1\n", V.back(), u);
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	n *= 2;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for(int i = 0; i < n; i++)
	{
		if (!sz[i])
		{
			dfs(i);

			if (sz[i]%2)
			{
				printf("IMPOSSIBLE\n");
				return 0;
			}
		}
	}

	printf("POSSIBLE\n");

	for (int i = 0; i < n; i++)
		if (!mark[i]) 
			dfs2(i);
}
