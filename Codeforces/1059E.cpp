// Codeforces 1059E - Split the Tree
// Lúcio Cardoso

// Solution is the same as the greedy one described in the editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n, L;
ll S;

int a[maxn];
int mx[maxn];

vector<int> grafo[maxn];

struct BinaryLifting
{
	int nivel[maxn];
	int tab[maxn][20];
	ll soma[maxn][20];

	void dfs(int u, int p)
	{
		for (auto v: grafo[u])
		{
			if (v == p) continue;

			nivel[v] = nivel[u]+1, tab[v][0] = u;
			soma[v][0] = a[u];

			dfs(v, u);
		}
	}

	void build(void)
	{
		for (int j = 1; j <= 19; j++)
		{
			for (int i = 1; i <= n; i++)
			{
				tab[i][j] = tab[tab[i][j-1]][j-1];
				soma[i][j] = soma[i][j-1] + soma[tab[i][j-1]][j-1];
			}
		}
	}

	int get(int u, ll k)
	{
		if (k < 0) return 0;

		int d = L-1;

		for (int i = 19; i >= 0; i--)
			if (tab[u][i] && d >= (1<<i) && k >= soma[u][i])
				d -= (1<<i), k -= soma[u][i], u = tab[u][i];

		return u;
	}
} LCA;

int dp[maxn], opt[maxn];

void solve(int u, int p, int d)
{
	int soma = 0;
	opt[u] = u;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		solve(v, u, d+1);
		soma += dp[v];
	}

	dp[u] = soma+1;

	for (auto v: grafo[u])
	{
		if (v == p || mx[opt[v]] > d) continue;

		if (dp[u] == soma+1 || mx[opt[v]] < mx[opt[u]])
		{
			dp[u] = soma;
			opt[u] = opt[v];
		}
	}
}

int main(void)
{
	scanf("%d %d %lld", &n, &L, &S);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 2; i <= n; i++)
	{
		int p;
		scanf("%d", &p);

		grafo[i].push_back(p);
		grafo[p].push_back(i);
	}

	if (*max_element(a+1, a+n+1) > S)
	{
		printf("-1\n");
		return 0;
	}

	LCA.dfs(1, 0); LCA.build();

	for (int i = 1; i <= n; i++)
		mx[i] = LCA.nivel[LCA.get(i, S-1ll*a[i])];

	solve(1, 0, 0);

	printf("%d\n", dp[1]);
}
