// Codeforces 662B - Graph Coloring
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, char> pii;

const int maxn = 1e5+10;

int n, m;

bool mark[maxn], on[maxn];

int ans = 1e9, qtd;
bool ok;
char C;

vector<pii> grafo[maxn];
vector<int> V, comp;

void dfs(int u)
{
	comp.push_back(u);
	mark[u] = true;

	if (on[u]) ++qtd;

	for (auto pp: grafo[u])
	{
		int v = pp.first, c = pp.second;

		if (mark[v])
		{
			if ((!on[u] && on[v]) || (on[u] && !on[v]))
			{
				if (c == C) ok = false;
			}
			else
			{
				if (c != C) ok = false;
			}

			continue;
		}

		if ((on[u] && c == C) || (!on[u] && c != C))
			on[v] = true;
		else
			on[v] = false;

		dfs(v);
	}
}

int getmin(int u)
{
	int q1 = 1e9, q2 = 1e9;

	comp.clear();
	ok = true, qtd = 0, on[u] = false;
	dfs(u);

	if (ok) q1 = qtd;

	for (auto v: comp)
		mark[v] = false;

	comp.clear();
	ok = true, qtd = 0, on[u] = true;
	dfs(u);

	if (ok) q2 = qtd;

	if (q1 == 1e9 && q2 == 1e9) return -1;

	if (q1 < q2)
	{
		for (auto v: comp)
			mark[v] = false;

		on[u] = false;
		dfs(u);
	}

	return min(q1, q2);
}

void get(char c)
{
	C = c;
	memset(mark, 0, sizeof mark); memset(on, 0, sizeof on);

	int tot = 0;

	for (int i = 1; i <= n; i++)
	{
		if (!mark[i])
		{
			int x = getmin(i);

			if (x == -1) return;

			tot += x;
		}
	}

	if (tot < ans)
	{
		ans = tot;
		V.clear();

		for (int i = 1; i <= n; i++)
			if (on[i])
				V.push_back(i);
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		char c;
		scanf("%d %d %c", &u, &v, &c);

		grafo[u].push_back({v, c});
		grafo[v].push_back({u, c});
	}

	get('R'); get('B');

	if (ans == 1e9) printf("-1\n");
	else
	{
		printf("%d\n", ans);
		for (auto u: V)
			printf("%d ", u);
		printf("\n");
	}
} 
