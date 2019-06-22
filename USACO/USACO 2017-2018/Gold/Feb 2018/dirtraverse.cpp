// USACO Gold Feb 2018 - Directory Traversal
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

int n;
int sz[maxn];

int leaf[maxn];

ll sub[maxn], ans[maxn];

vector<int> grafo[maxn];

void dfs1(int u, int p)
{
	if (grafo[u].size() == 1 && u != 1)
		leaf[u]++;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs1(v, u);

		leaf[u] += leaf[v];

		if (grafo[v].size() == 1)
			sub[u] += 1ll*sz[v];
		else
			sub[u] += (sub[v] + 1ll*(sz[v]+1ll)*leaf[v]);
	}
}

void dfs2(int u, int p)
{
	if (u == 1) 
		ans[u] = sub[u];
	else
		ans[u] = ans[p] - 1ll*(sz[u]+1ll)*leaf[u] + 3ll*(leaf[1]-leaf[u]);

	for (auto v: grafo[u])
		if (v != p)
			dfs2(v, u);
}

int main(void)
{
	freopen("dirtraverse.in", "r", stdin);
	freopen("dirtraverse.out", "w", stdout);
	
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		string s;
		int m;

		cin >> s;
		cin >> m;

		sz[i] = s.size();

		for (int j = 1; j <= m; j++)
		{
			int v;
			cin >> v;

			grafo[i].push_back(v); grafo[v].push_back(i);
		}
	}

	dfs1(1, 0);
	dfs2(1, 0);

	ll tot = 2e18+10;

	for (int i = 1; i <= n; i++)
		if (i == 1 || (grafo[i].size() > 1))
			tot = min(tot, ans[i]);

	cout << tot << "\n";
}
