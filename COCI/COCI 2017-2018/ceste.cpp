// COCI 2017/2018 - Ceste
// Lúcio Cardoso

// Solution: https://github.com/MohamedAhmed04/Competitive-programming/blob/master/COCI/COCI%2017-Ceste.cpp

// (I don't know yet why this solution passes, maybe test cases are weak)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 2e3+10;
const int maxv = 1e6+10;
const ll inf = 1e18+10;

int n;

int last[maxn];

ll ans[maxn];

vector<pair<pii, int>> grafo[maxn];

void dijkstra(void)
{
	for (int i = 1; i < maxn; i++)
		ans[i] = inf, last[i] = maxv;

	priority_queue<pair<pii, int>, vector<pair<pii, int>>, greater<pair<pii, int>>> fila;

	fila.push({{0, 0}, 1}), ans[1] = 0, last[1] = 0;

	while (!fila.empty())
	{
		int u = fila.top().second;
		int sum_c = fila.top().first.first, sum_t = fila.top().first.second;
		fila.pop();

		if (last[u] < sum_t) continue;

		last[u] = sum_t;
		ans[u] = min(ans[u], 1ll*sum_t*sum_c);

		for (auto pp: grafo[u])
		{
			int v = pp.second;
			int t = pp.first.second, c = pp.first.first;

			if (sum_t+t > maxv || sum_c+c > maxv) continue;

			fila.push({{sum_c+c, sum_t+t}, v});
		}
	}
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, t, c;
		scanf("%d %d %d %d", &u, &v, &t, &c);

		grafo[u].push_back({{c, t}, v});
		grafo[v].push_back({{c, t}, u});
	}

	dijkstra();

	for (int i = 2; i <= n; i++)
	{
		if (ans[i] == inf) printf("-1\n");
		else printf("%lld\n", ans[i]);
	}
}
