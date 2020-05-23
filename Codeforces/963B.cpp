// Codeforces 963B - Destruction of a Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int sz[maxn];

vector<int> grafo[maxn];

int dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
		if (v != p)
			sz[u] += dfs(v, u);

	return sz[u];
}

void solve(int u, int p)
{
	for (auto v: grafo[u])
		if (v != p && sz[v]%2 == 0)
			solve(v, u);

	printf("%d\n", u);

	for (auto v: grafo[u])
		if (v != p && sz[v]%2)
			solve(v, u);
}

int main(void)
{
	scanf("%d", &n);

	int root;
	for (int i = 1; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		if (!p) root = i;
		else
		{
			grafo[p].push_back(i);
			grafo[i].push_back(p);
		}
	}

	if (n%2 == 0)
	{
		printf("NO\n");
		return 0;
	}

	printf("YES\n");

	dfs(root, 0);
	solve(root, 0);
}
