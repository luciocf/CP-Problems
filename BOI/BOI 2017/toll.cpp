// BOI 2017 - Toll
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 5e4+10;
const ll inf = 1e18+10;

struct Query
{
	int block, a, b, ind;
};

int n, k;

ll ans[maxn];

ll dist[2][maxn];

vector<pii> grafo[2][maxn];
vector<Query> qry[maxn];

void calc_dist(int s, int q, int l, int r)
{
	for (int i = l; i <= r; i++)
		dist[q][i] = inf;

	dist[q][s] = 0;

	queue<int> fila;
	fila.push(s);

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto pp: grafo[q][u])
		{
			int v = pp.ff, w = pp.ss;

			if (v >= l && v <= r && dist[q][v] > dist[q][u] + 1ll*w)
			{
				dist[q][v] = dist[q][u] + 1ll*w;
				fila.push(v);
			}
		}
	}
}

void solve(int l, int r)
{
	if (l > r) return;

	int mid = (l+r)>>1;

	for (int u = k*mid; u < min(n, k*(mid+1)); u++)
	{
		calc_dist(u, 0, k*l, min(n-1, k*(r+1)-1)); calc_dist(u, 1,  k*l, min(n-1, k*(r+1)-1));

		for (int i = l; i <= mid; i++)
		{
			for (auto Q: qry[i])
			{
				if (Q.block < mid || Q.block == i) continue;
				if (Q.block > r) break;

				int a = Q.a, b = Q.b, ind = Q.ind;

				ans[ind] = min(ans[ind], dist[1][a] + dist[0][b]);
			}
		}
	}

	solve(l, mid-1); solve(mid+1, r);
}

int main(void)
{
	int m, q;
	scanf("%d %d %d %d", &k, &n, &m, &q);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[0][u].push_back({v, w});
		grafo[1][v].push_back({u, w});
	}

	for (int i = 1; i <= q; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		qry[a/k].push_back({b/k, a, b, i});
		ans[i] = inf;
	}

	for (int i = 0; i <= (n-1)/k; i++)
		sort(qry[i].begin(), qry[i].end(), [&] (Query a, Query b) {return a.block < b.block;});

	solve(0, (n-1)/k);

	for (int i = 1; i <= q; i++)
	{
		if (ans[i] == inf) printf("-1\n");
		else printf("%lld\n", ans[i]);
	}
}
