// APIO 2017 - Travelling Merchant
// Lúcio Cardoso

// Solution is the same as in: https://codeforces.com/blog/entry/51981?#comment-360508

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 110;
const int maxk = 1e3+10;
const ll inf = 1e18+10;

int n, m, k;
int b[maxn][maxk], s[maxn][maxk];

ll dist[maxn][maxn], g[maxn][maxn], p[maxn][maxn];

bool ok(int x)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (j == i || dist[i][j] == inf) p[i][j] = -inf;
			else p[i][j] = g[i][j] - 1ll*x*dist[i][j];
		}
	}

	for (int l = 1; l <= n; l++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				p[i][j] = max(p[i][j], p[i][l]+p[l][j]);

	for (int i = 1; i <= n; i++)
		if (p[i][i] >= 0)
			return true;

	return false;
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			scanf("%d %d", &b[i][j], &s[i][j]);

	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			dist[i][j] = dist[j][i] = inf;

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		dist[u][v] = min(dist[u][v], 1ll*w);
	}

	for (int l = 1; l <= n; l++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][l]+dist[l][j]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int l = 1; l <= k; l++)
				if (b[i][l] != -1 && s[j][l] != -1)
					g[i][j] = max(g[i][j], 1ll*s[j][l]-1ll*b[i][l]);

	int ini = 1, fim = 1e9+10, ans = 0;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	printf("%d\n", ans);
}
