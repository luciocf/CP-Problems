// Seletiva IOI 2017 - Caminhos
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

const int inf = 1e9+20;

const long long INF = 1e18+10;

const long long maxk = 1e16+10;

typedef pair<long long, int> pii;

typedef long long ll;

int D[maxn], P[maxn], n;

ll dist[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

void bfs(void)
{
	queue<int> fila;
	fila.push(1);

	for (int i = 2; i <= n; i++)
		D[i] = inf;

	mark[1] = 1;

	while (!fila.empty())
	{
		int x = fila.front();
		fila.pop();

		for (auto pp: grafo[x])
			if (!mark[pp.second])
				mark[pp.second] = 1, D[pp.second] = D[x]+1, fila.push(pp.second);
	}
}

void dijkstra(void)
{
	memset(mark, 0, sizeof mark);

	for (int i = 2; i <= n; i++)
		dist[i] = INF, P[i] = inf;

	priority_queue<pii, vector<pii>, greater<pii> > fila;
	fila.push({0LL, 1});

	while (!fila.empty())
	{
		int x = fila.top().second;
		fila.pop();

		if (mark[x]) continue;

		mark[x] = 1;
		for (auto pp: grafo[x])
		{
			int v = pp.second;
			ll d = pp.first;

			if (dist[v] > dist[x]+d)
			{
				dist[v] = dist[x]+(ll)d;
				P[v] = P[x]+1;
				fila.push({dist[v], v});
			}
			else if (dist[v] == dist[x]+d)
				P[v] = min(P[v], P[x]+1);
		}
	}
}

bool ok(ll k)
{
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < grafo[i].size(); j++)
			grafo[i][j].first += k;

	dijkstra();

	bool ok = 1;
	for (int i = 2; i <= n; i++)
		if (D[i] != P[i] || D[i] == inf)
			ok = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < grafo[i].size(); j++)
			grafo[i][j].first -= k;

	return ok;
}

ll busca(void)
{
	ll ini = 0LL, fim = maxk, ans = -1LL;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	int m;
	cin >> n >> m;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		ll d;
		cin >> u >> v >> d;

		grafo[u].push_back({d, v});
		grafo[v].push_back({d, u});
	}

	bfs();

	cout << busca() << "\n";
}