// CodeChef MYS00T - Mystery Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int sz[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (!mark[v] && v != p)
		{
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

int centroid(int u, int p, int S)
{
	for (auto v: grafo[u])
		if (!mark[v] && v != p && sz[v] > S/2)
			return centroid(v, u, S);

	return u;
}

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n;
		scanf("%d", &n);

		memset(mark, 0, sizeof mark);
		for (int i = 1; i <= n; i++)
			grafo[i].clear();

		for (int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			grafo[u].push_back(v); grafo[v].push_back(u);
		}

		dfs(1, 0);
		int c = centroid(1, 0, n);

		while (true)
		{
			printf("1 %d\n", c);
			fflush(stdout);

			int v;
			scanf("%d", &v);

			if (v == -1)
			{
				printf("2 %d\n", c);
				fflush(stdout);

				break;
			}

			mark[c] = 1;
			dfs(v, c);

			c = centroid(v, 0, sz[v]);
		}

		int one;
		scanf("%d", &one);
	}
}
