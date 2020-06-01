// Codeforces 1363E - Tree Shuffling
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int a[maxn], b[maxn], c[maxn];

int has[2][maxn];

long long ans;

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	if (b[u] != c[u])
		has[b[u]][u]++;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		a[v] = min(a[v], a[u]);

		dfs(v, u);

		has[0][u] += has[0][v], has[1][u] += has[1][v];
	}

	int x = min(has[0][u], has[1][u]);

	ans += 2ll*a[u]*x;

	has[0][u] -= x;
	has[1][u] -= x;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &a[i], &b[i], &c[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0);

	if (has[0][1] != has[1][1])
	{
		printf("-1\n");
		return 0;
	}

	printf("%lld\n", ans);
}
