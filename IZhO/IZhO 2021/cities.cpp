// IZhO 2021 - Cities
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 1e6+10;
const ll inf = 1e18+10;

int n, s, t;
int a[maxn];

ll dist[maxn];
bool mark[maxn];

vector<pii> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i <= n; i++)
		dist[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii>> fila;

	dist[s] = 0;
	fila.push({0, s});

	while (!fila.empty())
	{
		int u = fila.top().ss; fila.pop();

		if (mark[u]) continue;
		mark[u] = 1;

		for (auto pp: grafo[u])
		{
			int v = pp.ff;
			ll w = pp.ss;

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
	scanf("%d %d %d", &n, &s, &t);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	stack<int> stk;

	for (int i = 1; i <= n; i++)
	{
		while (stk.size() && a[stk.top()] >= a[i])
			stk.pop();

		if (stk.size()) grafo[i].push_back({stk.top(), 1ll*a[i]*(i-stk.top())});

		stk.push(i);
	}

	while (stk.size()) stk.pop();

	for (int i = n; i >= 1; i--)
	{
		while (stk.size() && a[stk.top()] >= a[i])
			stk.pop();

		if (stk.size()) grafo[i].push_back({stk.top(), 1ll*a[i]*(stk.top()-i)});

		stk.push(i);
	}

	dijkstra();

	ll ans = inf;
	for (int i = 1; i <= n; i++)
		ans = min(ans, dist[i] + 1ll*a[i]*abs(t-i));

	printf("%lld\n", ans);
}
