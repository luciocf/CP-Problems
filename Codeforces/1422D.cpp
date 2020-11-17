// Codeforces 1422D - Returning Home
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int inf = 2e9+10;

struct Pt
{
	int x, y, ind;
} a[maxn];

int dist[maxn];
bool mark[maxn];

vector<pii> grafo[maxn];

int getdist(int i, int j)
{
	return min(abs(a[i].x - a[j].x), abs(a[i].y - a[j].y));
}

void dijkstra(int n)
{
	for (int i = 0; i <= n; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	dist[0] = 0, fila.push({0, 0});

	while (!fila.empty())
	{
		int u = fila.top().ss; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff, w = pp.ss;

			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				fila.push({dist[v], v});
			}
		}
	}
}

int main(void)
{
	int n, m, dx, dy;
	scanf("%d %d %d %d %d %d", &m, &n, &a[0].x, &a[0].y, &dx, &dy);

	a[0].ind = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &a[i].x, &a[i].y);
		a[i].ind = i;
	}

	sort(a, a+n+1, [&] (Pt a, Pt b) {return a.x < b.x;});

	for (int i = 0; i <= n; i++)
	{
		if (i > 0) grafo[a[i].ind].push_back({a[i-1].ind, getdist(i, i-1)});

		if (i < n) grafo[a[i].ind].push_back({a[i+1].ind, getdist(i, i+1)});
	}

	sort(a, a+n+1, [&] (Pt a, Pt b) {return a.y < b.y;});

	for (int i = 0; i <= n; i++)
	{
		if (i > 0) grafo[a[i].ind].push_back({a[i-1].ind, getdist(i, i-1)});

		if (i < n) grafo[a[i].ind].push_back({a[i+1].ind, getdist(i, i+1)});
	}

	dijkstra(n);

	long long ans = inf;

	for (int i = 0; i <= n; i++)
		ans = min(ans, 1ll*dist[a[i].ind] + 1ll*abs(a[i].x-dx) + 1ll*abs(a[i].y-dy));

	printf("%lld\n", ans);
}
