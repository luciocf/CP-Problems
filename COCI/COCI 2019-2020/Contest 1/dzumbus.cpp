// COCI 2019/2020 - Dzumbus
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e3+10;
const ll inf = 1e18+10;

int n;
int a[maxn];

int sz[maxn];

int pai[maxn], peso[maxn];

ll dp[maxn][maxn][2];
ll mn[maxn];

vector<int> grafo[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

void dfs(int u, int p)
{
	dp[u][0][1] = inf;
	for (int i = 1; i <= n; i++)
		dp[u][i][0] = dp[u][i][1] = inf;

	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);
		sz[u] += sz[v];

		for (int i = sz[u]; i >= 1; i--)
		{
			for (int j = min(i, sz[v]); j >= 1 && i-j <= sz[u]-sz[v]; j--)
			{
				ll caso1 = (i-j >= 1 ? dp[u][i-j-1][0] + 1ll*a[u] + dp[v][j][1] : inf);
				ll caso2 = (i-j >= 1 ? dp[u][i-j-1][0] + 1ll*a[u] + dp[v][j-1][0] + 1ll*a[v] : inf);
				ll caso3 = dp[u][i-j][1] + dp[v][j][0];
				ll caso4 = dp[u][i-j][1] + dp[v][j][1];
				ll caso5 = dp[u][i-j][1] + dp[v][j-1][0] + 1ll*a[v];

				dp[u][i][1] = min({dp[u][i][1], caso1, caso2, caso3, caso4, caso5});
			}
		}

		for (int i = sz[u]; i >= 1; i--)
			for (int j = min(i, sz[v]); j >= 1 && i-j <= sz[u]-sz[v]; j--)
				dp[u][i][0] = min(dp[u][i][0], dp[u][i-j][0] + min(dp[v][j][0], dp[v][j][1]));

	}
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	init();

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);

		Join(u, v);
	}

	a[0] = 1e9+10;
	for (int i = 1; i <= n; i++)
		if (Find(i) == i)
			grafo[0].push_back(i);

	dfs(0, 0);

	mn[n] = dp[0][n][0];
	for (int i = n-1; i >= 1; i--)
		mn[i] = min(mn[i+1], dp[0][i][0]);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int S;
		scanf("%d", &S);

		int ini = 0, fim = n, ans = 0;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (mn[mid] <= S) ans = mid, ini = mid+1;
			else fim = mid-1;
		}

		printf("%d\n", ans);
	}
}
