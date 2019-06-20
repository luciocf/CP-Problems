// USACO Platinum Feb 2019 - Moorio Kart
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2510;
const int mod = 1e9+7;

typedef pair<int, int> pii;

int n, m, x, y;

int comp[maxn];
int dist[maxn][maxn];

pii soma[maxn];

pii dp[maxn][maxn];

pair<int, long long> qtd[maxn][maxn];

vector<pii> grafo[maxn];
vector<pair<int, pii>> freq[maxn];

void add(int &a, int b)
{
	a = (a+b)%mod;
}

void dfs(int u, int p, int cc)
{
	comp[u] = cc;

	for (auto v: grafo[u])
		if (v.first != p)
			dfs(v.first, u, cc);
}

void dfs2(int u, int p, int root)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p) continue;

		dist[root][v] = dist[root][u]+w;

		int d = min(y, dist[root][v]);

		if (v > root)
		{
			qtd[comp[root]][d].first++;
			qtd[comp[root]][d].second += 1ll*dist[root][v];
		}

		dfs2(v, u, root);
	}
}

int main(void)
{
	FILE *fin = fopen("mooriokart.in", "r");
	FILE *fout = fopen("mooriokart.out", "w");

	fscanf(fin, "%d %d %d %d", &n, &m, &x, &y);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		fscanf(fin, "%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	int k = 0;

	for (int i = 1; i <= n; i++)
	{
		if (comp[i]) continue;

		dfs(i, 0, ++k);
	}

	for (int i = 1; i <= n; i++)
		dfs2(i, 0, i);

	for (int i = 1; i <= k; i++)
		for (int j = 0; j <= y; j++)
			if (qtd[i][j].first > 0)
				freq[i].push_back({j, {qtd[i][j].first, qtd[i][j].second%mod}});

	dp[0][min(y, k*x)] = {1, k*x};

	for (int i = 1; i <= k; i++)
	{
		for (int j = 0; j <= y; j++)
		{
			for (auto pp: freq[i])
			{
				int v = pp.first, t = pp.second.first, w = pp.second.second;

				int d = min(y, j+v);
		
				add(dp[i][d].first, (1ll*dp[i-1][j].first*t)%mod);
				add(dp[i][d].second, ((1ll*dp[i-1][j].first*w)%mod + (1ll*dp[i-1][j].second*t)%mod)%mod);
			}
		}
	}

	for (int i = 1; i < k; i++)
		dp[k][y].second = (2ll*dp[k][y].second*i)%mod;

	fprintf(fout, "%d\n", dp[k][y].second);
}
