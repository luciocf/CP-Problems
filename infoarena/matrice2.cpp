// infoarena - Matrice 2
// Lúcio Cardoso

// Solution:

// Insert the matrix numbers in decreasing order of value in a DSU structure.
// When joining two sets, keep an array that stores the "time" that the operation was done
// in the head of the smallest component (i.e add an edge of weight equal to the time of the insertion
// in the DSU tree). The time of a Join operation is the order of the number being inserted (i.e 10^6 is the
// first to be inserted, 10^6-2 is the second, etc.)

// Since the height of the DSU tree (without path compression) is O(log n), we can answer the
// queries in O(log n) by finding the largest weight in the path from (x1, y1) to (x2, y2) in the tree.
// The answer is 10^6 - (largest_weight) + 1.

// Idea is similar to Pictionary from COCI 2017/2018: http://blog.brucemerry.org.za/2018/01/coci-20172018-r5-analysis.html

#include <bits/stdc++.h>

using namespace std;

const int maxn = 302;
const int maxv = 90002;

int n, q;
int tab[maxn][maxn];

int pai[maxv], peso[maxv], nivel[maxv], edge[maxv];

vector<int> V[maxv];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void init(void)
{
	for (int i = 1; i <= n*n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return Find(pai[x]);
}

void Join(int x, int y, int tt)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y], edge[y] = tt;
}

int dfs(int u)
{
	if (u == Find(u)) return (nivel[u] = 0);
	if (nivel[u] != -1) return nivel[u];

	nivel[u] = dfs(pai[u])+1;
	return nivel[u];
}

int get(int u, int v)
{
	int mx = 0;

	while (u != v)
	{
		if (nivel[u] > nivel[v])
		{
			mx = max(mx, edge[u]);
			u = pai[u];
		}
		else
		{
			mx = max(mx, edge[v]);
			v = pai[v];
		}
	}

	return mx;
}

int main(void)
{
	freopen("matrice2.in", "r", stdin);
	freopen("matrice2.out", "w", stdout);

	scanf("%d %d", &n, &q);

	map<int, int> mp;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &tab[i][j]);

			mp[tab[i][j]] = 0;
		}
	}

	int aux = 0;

	for (auto &x: mp)
		x.second = ++aux;

	aux = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			V[mp[tab[i][j]]].push_back(++aux);

	init();

	int tt = 0;

	for (int T = 1000000; T >= 1; T--)
	{
		++tt;
		if (mp.find(T) == mp.end()) continue;

		for (auto p: V[mp[T]])
		{
			int x = (p-1)/n + 1, y = (p-x*n+n);

			for (int i = 0; i < 4; i++)
			{
				int a = x+linha[i], b = y+coluna[i];

				if (a < 1 || a > n || b < 1 || b > n || tab[a][b] < T) continue;

				Join((x-1)*n + y, (a-1)*n + b, tt);
			}
		}
	}

	memset(nivel, -1, sizeof nivel);

	for (int i = 1; i <= n*n; i++)
		if (nivel[i] == -1)
			dfs(i);

	for (int i = 1; i <= q; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		int mx = get((x1-1)*n+y1, (x2-1)*n+y2);

		printf("%d\n", 1000000-mx+1);
	}
}
