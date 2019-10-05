// COCI 2008/2009 - Dostava
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2009/contest6_solutions

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e3+10;
const int maxm = 210;

int n, m;
int a[maxn][maxm];

int soma[2][maxn], soma_linha[maxn];
int pref[maxn][maxm], suf[maxn][maxm];

int mn[maxn];

int dist[2*maxn][2*maxn];

bool mark[2*maxn];

vector<pii> grafo[2*maxn];

void dijkstra(int s)
{
	memset(mark, 0, sizeof mark);

	for (int i = 1; i <= 2*n; i++)
		dist[s][i] = 1e9+10;

	dist[s][s] = 0;

	priority_queue<pii, vector<pii>, greater<pii>> fila;
	fila.push({dist[s][s], s});

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.first, w = pp.second;

			if (dist[s][v] > dist[s][u]+w)
			{
				dist[s][v] = dist[s][u]+w;
				fila.push({dist[s][v], v});
			}
		}
	}
}

int get(int u, int x, int y)
{
	int ans = dist[u][x] + pref[x][y] - a[x][1];
	ans = min(ans, dist[u][x+n] + suf[x][y] - a[x][m]);

	return ans;
}

int walk(int x, int l, int r)
{
	if (l > r) swap(l, r);

	return pref[x][r]-pref[x][l-1];
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);

			soma_linha[i] += a[i][j];
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			pref[i][j] = pref[i][j-1]+a[i][j];

		for (int j = m; j >= 1; j--)
			suf[i][j] = suf[i][j+1]+a[i][j];
	}

	for (int i = 1; i <= n; i++)
	{
		soma[0][i] = soma[0][i-1]+a[i][1];

		soma[1][i] = soma[1][i-1]+a[i][m];
	}

	for (int i = 1; i <= n; i++)
	{
		mn[i] = 1e9+10;

		for (int j = i; j >= 1; j--)
			mn[i] = min(mn[i], (soma[0][i]-soma[0][j]) + (soma[1][i]-soma[1][j]) + soma_linha[j]);

		for (int j = i+1; j <= n; j++)
			mn[i] = min(mn[i], (soma[0][j-1]-soma[0][i-1]) + (soma[1][j-1]-soma[1][i-1]) + soma_linha[j]);
	}

	for (int i = 1; i <= n; i++)
	{
		grafo[i].push_back({n+i, mn[i]-a[i][1]});
		grafo[n+i].push_back({i, mn[i]-a[i][m]});

		if (i < n)
		{
			grafo[i].push_back({i+1, a[i+1][1]});
			grafo[i+1].push_back({i, a[i][1]});

			grafo[n+i].push_back({n+i+1, a[i+1][m]});
			grafo[n+i+1].push_back({n+i, a[i][m]});
		}
	}

	for (int i = 1; i <= n; i++)
	{
		dijkstra(i);
		dijkstra(i+n);
	}
	
	int d;
	scanf("%d", &d);

	int x = 1, y = 1;
	long long ans = a[1][1];

	for (int i = 1; i <= d; i++)
	{
		int A, B;
		scanf("%d %d", &A, &B);

		int mn = pref[x][y-1] + get(x, A, B);
		mn = min(mn, suf[x][y+1] + get(x+n, A, B));

		if (A == x)
			mn = min(mn, walk(x, y, B)-a[x][y]);

		ans += 1ll*mn;

		x = A, y = B;
	}

	printf("%lld\n", ans);
}
