// Codeforces 453C - Little Pony and Summer Sun Celebration
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n, m;
int a[maxn];

int comp[maxn], cc;
bool mark[maxn];

int qtd[maxn];

vector<int> grafo[maxn], ans;

void dfs(int u, int cc)
{
	comp[u] = cc;

	for (auto v: grafo[u])
		if (!comp[v])
			dfs(v, cc);
}

void solve(int u, int p)
{
	ans.push_back(u), ++qtd[u];
	mark[u] = 1;

	for (auto v: grafo[u])
	{
		if (mark[v]) continue;

		solve(v, u);

		if (qtd[v]%2 != a[v])
		{
			ans.push_back(u); ans.push_back(v);
			++qtd[u];
			++qtd[v];
		}

		if (!p && qtd[u]%2 == a[u]) return;

		++qtd[u];
		ans.push_back(u);
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	int u = -1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		if (a[i]) u = i;
	}

	if (u == -1)
	{
		printf("0\n");
		return 0;
	}

	for (int i = 1; i <= n; i++)
		if (!comp[i])
			dfs(i, ++cc);

	for (int i = 1; i <= n; i++)
	{
		if (a[i] && comp[i] != comp[u])
		{
			printf("-1\n");
			return 0;
		}
	}

	solve(u, 0);

	printf("%d\n", (int)ans.size());
	for (auto v: ans)
		printf("%d ", v);
	printf("\n");
}
