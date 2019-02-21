// CEOI 2017 - Chase
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int maxv = 110;

typedef long long ll;

int n, c;
int num[maxn];

ll soma[maxn], ans;
ll d[2][maxn][maxv], ant[2][maxn][maxv], ant2[maxv];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		for (int i = 1; i <= c; i++)
		{
			ll D = max(d[0][v][i], d[0][v][i-1]+soma[v]-(ll)num[u]);

			if (D > d[0][u][i]) d[1][u][i] = d[0][u][i], d[0][u][i] = D;
			else if (D > d[1][u][i]) d[1][u][i] = D;
		}
	}
}

void rotate(int u, int p)
{
	for (int i = 1; i <= c; i++)
		ans = max({ans, d[0][u][i], d[0][u][i-1]+soma[u]});

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		for (int i = 1; i <= c; i++)
			ant2[i] = d[0][v][i]; 

		for (int i = 1; i <= c; i++)
		{
			ant[0][u][i] = d[0][u][i], ant[1][u][i] = d[1][u][i];

			ll D = max(d[0][v][i], ant2[i-1]+soma[v]-(ll)num[u]);

			if (d[0][u][i] == D) d[0][u][i] = d[1][u][i];

			D = max(d[0][u][i], d[0][u][i-1]+soma[u]-(ll)num[v]);

			if (D > d[0][v][i]) d[1][v][i] = d[0][v][i], d[0][v][i] = D;
			else if (D > d[1][v][i]) d[1][v][i] = D;
		}

		rotate(v, u);

		for (int i = 1; i <= c; i++)
			d[0][u][i] = ant[0][u][i], d[1][u][i] = ant[1][u][i];
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> n >> c;

	for (int i = 1; i <= n; i++)
		cin >> num[i];

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	for (int u = 1; u <= n; u++)
		for (auto v: grafo[u])
			soma[u] += (ll)num[v];

	dfs(1, 0); rotate(1, 0);

	cout << ans << "\n"; 
}
