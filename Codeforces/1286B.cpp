// Codeforces 1286B - Numbers on Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;

int a[maxn], c[maxn];

vector<int> grafo[maxn];

bool dfs(int u, int p, int at)
{
	if (a[u] == 0 && c[u] == 0)
	{
		a[u] = at+1;
		return true;
	}

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		if (dfs(v, u, at))
		{
			c[u]--;
			return true;
		}
	}

	return false;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int root;

	for (int i = 1; i <= n; i++)
	{
		int p;
		scanf("%d %d", &p, &c[i]);

		if (p)
		{
			grafo[i].push_back(p);
			grafo[p].push_back(i);
		}
		else root = i;
	}

	int at = 0;

	for (int i = 1; i <= n; i++)
	{
		if (!dfs(root, 0, at))
		{
			printf("NO\n");
			return 0;
		}

		at++;
	}

	printf("YES\n");
	for (int i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");
}
