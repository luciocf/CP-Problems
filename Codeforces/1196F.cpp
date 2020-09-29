// Codeforces 1196F - K-th Path
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

struct Edge
{
	int u, v, w;
} edge[maxn];

int pos[maxn];

ll dist[810][810];

int main(void)
{
	int n, m, K;
	scanf("%d %d %d", &n, &m, &K);

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		edge[i] = {u, v, w};
	}

	sort(edge+1, edge+m+1, [&] (Edge a, Edge b) {return a.w < b.w;});

	vector<int> vert;

	for (int i = 1; i <= min(m, K); i++)
	{
		vert.push_back(edge[i].u);
		vert.push_back(edge[i].v);
	}

	sort(vert.begin(), vert.end());
	vert.erase(unique(vert.begin(), vert.end()), vert.end());

	for (int i = 0; i < vert.size(); i++)
		pos[vert[i]] = i;

	for (int i = 0; i < vert.size(); i++)
		for (int j = 0; j < vert.size(); j++)
			if (i != j)
				dist[i][j] = inf;

	for (int i = 1; i <= min(m, K); i++)
	{
		int u = edge[i].u, v = edge[i].v;
		ll w = edge[i].w;

		u = pos[u], v = pos[v];

		dist[u][v] = min(dist[u][v], w), dist[v][u] = min(dist[v][u], w);
	}

	for (int k = 0; k < vert.size(); k++)
		for (int i = 0; i < vert.size(); i++)
			for (int j = 0; j < vert.size(); j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	vector<ll> V;
	for (auto i: vert)
		for (auto j: vert)
			if (i < j)
				V.push_back(dist[pos[i]][pos[j]]);

	sort(V.begin(), V.end());

	printf("%lld\n", V[K-1]);

}
