// Codeforces 958B2 - Maximum Control (medium)
// Lúcio Cardoso

// Solution: Same as editorial

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int n;

int nivel[maxn], pai[maxn];
int dist[maxn], leaf[maxn];

vector<int> grafo[maxn];

set<pii> st;

void dfs1(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;

		dfs1(v, u);
	}
}

void dfs2(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pai[v] = u;

		dfs2(v, u);

		if (1+dist[v] > dist[u])
		{
			dist[u] = 1+dist[v];
			leaf[u] = leaf[v];
		}
	}

	if (!dist[u]) leaf[u] = u;

	if (p) st.insert({-dist[u], u});
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs1(1, 0);

	int root, mx = -1;
	for (int i = 1; i <= n; i++)
		if (nivel[i] > mx)
			mx = nivel[i], root = i;

	dfs2(root, 0);

	int it = 2, ans = 1;
	printf("%d ", ans);

	while (st.size())
	{
		int u = st.begin()->second; st.erase(st.begin());

		ans++;

		for (int v = leaf[u]; v != u; v = pai[v])
		{
			++ans;
			st.erase({-dist[v], v});
		}

		printf("%d ", ans);
		++it;
	}

	for (int i = it; it <= n; it++)
		printf("%d ", ans);

	printf("\n");
}
