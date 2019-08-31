// POI 2010 - Sums
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/POI10-sums-Mohamed_Nasser.pdf


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 5e4+10;
const ll inf = 1e18+10;

int n;
int a[maxn];

ll dist[maxn];

bool mark[maxn];

void dijkstra(void)
{
	for (int i = 1; i < maxn; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	fila.push({0, 0}), dist[0] = 0;

	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (int i = 1; i <= n; i++)
		{
			int v = (a[i]+u)%a[1];
			int w = a[i];

			if (dist[v] > dist[u]+1ll*w)
			{
				dist[v] = dist[u]+1ll*w;
				fila.push({dist[v], v});
			}
		}
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	dijkstra();

	int m;
	scanf("%d", &m);

	for (int i = 1; i <= m; i++)
	{
		ll x;
		scanf("%lld", &x);

		if (dist[x%a[1]] == inf)
		{
			printf("NIE\n");
			continue;
		}

		if (dist[x%a[1]] <= x)
			printf("TAK\n");
		else
			printf("NIE\n");
	}
}
