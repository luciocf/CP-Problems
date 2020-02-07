// Codeforces 506D - Mr. Kitayuta's Colorful Graph
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int sq = 500;

int n;

int grau[maxn];
int ind_heavy[maxn];

int pai[maxn], peso[maxn];

int ind_cc[maxn];
bool mark[maxn];

int ans[sq][maxn];

vector<int> comp[maxn];
vector<int> aparece[maxn];

vector<pii> edge[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);

		edge[c].push_back({u, v});
		grau[u]++, grau[v]++;
	}

	init();

	int cc = 0;

	for (int i = 1; i <= m; i++)
	{
		for (auto e: edge[i])
		{
			int u = e.first, v = e.second;
			Join(u, v);
		}

		for (auto e: edge[i])
		{
			int u = e.first, v = e.second;

			if (Find(u) == u && ind_cc[u] == 0)
				ind_cc[u] = ++cc;

			if (Find(v) == v && ind_cc[v] == 0)
				ind_cc[v] = ++cc;
		}

		for (auto e: edge[i])
		{
			int u = e.first, v = e.second;

			if (mark[u] == 0)
			{
				comp[ind_cc[Find(u)]].push_back(u);
				aparece[u].push_back(ind_cc[Find(u)]);

				mark[u] = 1;
			}

			if (mark[v] == 0)
			{
				comp[ind_cc[Find(v)]].push_back(v);
				aparece[v].push_back(ind_cc[Find(v)]);
				
				mark[v] = 1;
			}
		}

		for (auto e: edge[i])
		{
			int u = e.first, v = e.second;

			pai[u] = u, pai[v] = v;
			peso[u] = peso[v] = 1;
			ind_cc[u] = ind_cc[v] = mark[u] = mark[v] = 0;
		}
	}

	int ind_h = 0;
	for (int i = 1; i <= n; i++)
		if (grau[i] > sq)
			ind_heavy[i] = ++ind_h;

	for (int i = 1; i <= n; i++)
		if (ind_heavy[i] != 0)
			for (auto j: aparece[i])
				for (auto v: comp[j])
					ans[ind_heavy[i]][v]++;

	for (int i = 1; i <= n; i++)
		sort(aparece[i].begin(), aparece[i].end());

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		if (ind_heavy[u])
		{
			printf("%d\n", ans[ind_heavy[u]][v]);
			continue;
		}

		if (ind_heavy[v])
		{
			printf("%d\n", ans[ind_heavy[v]][u]);
			continue;
		}

		int l = 0, r = 0;
		int tot = 0;

		while (l < aparece[u].size() && r < aparece[v].size())
		{
			if (aparece[u][l] == aparece[v][r])
			{
				tot++;
				l++, r++;
			}
			else if (aparece[u][l] < aparece[v][r])
				l++;
			else
				r++;
		}

		printf("%d\n", tot);
	}
}
