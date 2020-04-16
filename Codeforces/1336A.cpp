// Codeforces 1336A - Linova and Kingdom
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int sub[maxn], nivel[maxn];

vector<int> grafo[maxn];
vector<int> V;

void dfs(int u, int p)
{
	sub[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;

		dfs(v, u);

		sub[u] += sub[v];
	}

	V.push_back(sub[u] - nivel[u]);
}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	nivel[1] = 1;
	dfs(1, 0);

	sort(V.begin(), V.end(), greater<int>());

	long long ans = 0;

	for (int i = 1; i <= n-k; i++)
		ans += 1ll*V[i-1];

	printf("%lld\n", ans);
}
