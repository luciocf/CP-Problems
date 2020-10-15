// COI 2019 - Izlet
// Lúcio Cardoso

// Solution is the same as the mentioned here: https://codeforces.com/blog/entry/66506?#comment-505659

#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 3e3+10;
 
int a[maxn][maxn];
 
int cor[maxn];
vector<pii> edge;
 
vector<int> grafo[maxn];
 
struct DSU
{
	int pai[maxn], peso[maxn];
 
	void init(int n)
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
} dsu;

int qtd[maxn];
int cc, tot;

int dfs(int u, int p, int root)
{
	if (cor[u])
	{
		++qtd[cor[u]];
		if (qtd[cor[u]] == 1) ++tot;
	}

	if (cor[u] && tot == a[root][u]) return cor[u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		int c = dfs(v, u, root);
		if (c) return c;
	}

	if (cor[u])
	{
		--qtd[cor[u]];
		if (qtd[cor[u]] == 0) --tot;
	}

	return 0;
}

int get_cor(int u)
{
	memset(qtd, 0, sizeof qtd); tot = 0;

	int c = dfs(u, 0, u);

	return (c ? c : ++cc);
}

void paint(int u, int p)
{
	cor[u] = get_cor(u);

	for (auto v: grafo[u])
		if (v != p)
			paint(v, u);
}
 
int main(void)
{
	int s;
	scanf("%d", &s);
 
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
 
	dsu.init(n);
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = i+1; j <= n; j++)
		{
			if (a[i][j] == 1 && dsu.Find(i) != dsu.Find(j))
			{
				edge.push_back({i, j});
				dsu.Join(i, j);
 
				grafo[i].push_back(j);
				grafo[j].push_back(i);
			}
		}
	}
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = i+1; j <= n; j++)
		{
			if (a[i][j] == 2 && dsu.Find(i) != dsu.Find(j))
			{
				edge.push_back({i, j});
				dsu.Join(i, j);
 
				grafo[i].push_back(j);
				grafo[j].push_back(i);
			}
		}
	}
 
	paint(1, 0);
 
	for (int i = 1; i <= n; i++)
		printf("%d ", cor[i]);

	printf("\n");

	for (int i = 1; i < n; i++)
		printf("%d %d\n", edge[i-1].first, edge[i-1].second);
}
