// Codeforces 858F - Wizard's Tour
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int nivel[maxn];
bool mark[maxn], usou[maxn];

vector<int> grafo[maxn];

vector<int> back[maxn];

vector<pair<int, pii>> ans;

void dfs(int u, int p)
{
	mark[u] = 1;

	for (auto v: grafo[u])
	{
		if (mark[v])
		{
			if (v != p && nivel[u] < nivel[v]) back[v].push_back(u);
			continue;
		}

		nivel[v] = nivel[u]+1;

		dfs(v, u);
	}
}

void solve(int u, int p)
{
	mark[u] = 1;

	vector<int> lista;

	for (auto v: grafo[u])
	{
		if (mark[v]) continue;

		solve(v, u);
		if (!usou[v]) lista.push_back(v);
	}


	for (int i = 1; i < lista.size(); i += 2)
		ans.push_back({lista[i-1], {u, lista[i]}});

	if (!back[u].size())
	{
		if (p && lista.size()%2)
		{
			usou[u] = 1;
			ans.push_back({lista.back(), {u, p}});
		}
	}
	else
	{
		if (lista.size()%2)
			ans.push_back({lista.back(), {u, back[u].back()}});
		else
		{
			usou[u] = 1;
			ans.push_back({p, {u, back[u].back()}});
		}
	}
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i, 0);

	for (int i = 1; i <= n; i++)
	{
		while (back[i].size() >= 2)
		{
			int a = back[i].back(); back[i].pop_back();
			int b = back[i].back(); back[i].pop_back();

			ans.push_back({a, {i, b}});
		}
	}

	memset(mark, 0, sizeof mark);

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			solve(i, 0);

	printf("%d\n", (int)ans.size());
	for (auto pp: ans)
		printf("%d %d %d\n", pp.ff, pp.ss.ff, pp.ss.ss);
}
