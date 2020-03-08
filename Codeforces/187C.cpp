// Codeforces 187C - Weak Memory
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n, m, k, S, T;

int pai[maxn], peso[maxn];

bool mark[maxn];

int dist[maxn], source[maxn];

vector<int> grafo[maxn];

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

void bfs(void)
{
	queue<int> fila;

	for (int i = 1; i <= n; i++)
	{
		if (mark[i])
		{
			fila.push(i);
			dist[i] = 0, source[i] = i;
		}
	}

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (source[v] == 0)
			{
				dist[v] = dist[u]+1;
				source[v] = source[u];

				fila.push(v);
			}
		}
	}
}

bool ok(int x)
{
	init();

	for (int i = 1; i <= n; i++)
		for (auto v: grafo[i])
			if (dist[i]+dist[v]+1 <= x)
				Join(source[i], source[v]);

	return (Find(S) == Find(T));
}

int busca(void)
{
	int ini = 0, fim = m, ans = -1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= k; i++)
	{
		int u;
		scanf("%d", &u);

		mark[u] = 1;
	}

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	scanf("%d %d", &S, &T);
	mark[T] = 1;

	bfs();

	printf("%d\n", busca());
}
