// DMOJ - Summer Institute '17 Contest 3 P5 - Balanced Cycles
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int sz[maxn];

bool mark[maxn];

map<int, int> qtd;
ll ans;

vector<pii> grafo[maxn];

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto e: grafo[u])
	{
		int v = e.first;
		if (v == p || mark[v]) continue;

		dfs(v, u);

		sz[u] += sz[v];
	}
}

int centroid(int u, int p, int S)
{
	for (auto e: grafo[u])
	{
		int v = e.first;

		if (v != p && !mark[v] && sz[v] > S/2)
			return centroid(v, u, S);
	}

	return u;
}

void upd(int u, int p, int A, int B, int x)
{
	qtd[2*B - A] += x;

	for (auto e: grafo[u])
	{
		int v = e.first, w = e.second;

		if (v != p && !mark[v])
			upd(v, u, A+1, B+w, x);
	}
}

void calc(int root, int u, int p, int A, int B)
{
	ans += 1ll*qtd[A - 2*B + 1];
	if ((A - 2*B + 1) == 0 && p == root) ans--; 

	for (auto e: grafo[u])
	{
		int v = e.first, w = e.second;

		if (v != p && !mark[v])
			calc(root, v, u, A+1, B+w);
	}
}

void decompose(int u)
{
	dfs(u, 0);

	int c = centroid(u, 0, sz[u]);
	mark[c] = 1;

	qtd[0]++;

	for (auto e: grafo[c])
	{
		int v = e.first, w = e.second;
		if (mark[v]) continue;

		calc(c, v, c, 1, w);
		upd(v, c, 1, w, 1);
	}

	upd(c, 0, 0, 0, -1);

	for (auto e: grafo[c])
		if (!mark[e.first])
			decompose(e.first);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		char c;

		scanf("%d %d %c", &u, &v, &c);

		int w = (c == 'r' ? 1 : 0);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	decompose(1);

	qtd.clear();
	memset(mark, 0, sizeof mark);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < grafo[i].size(); j++)
		{
			if (grafo[i][j].second == 0) grafo[i][j].second = 1;
			else grafo[i][j].second = 0;
		}
	}

	decompose(1);

	printf("%lld\n", ans);
}
