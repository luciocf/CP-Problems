// Codeforces 1243D - 0-1 MST
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;

set<int> lista;

set<int> grafo[maxn];

void bfs(int S)
{
	queue<int> fila;
	fila.push(S);

	lista.erase(S);

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		int ant = 0;

		for (auto v: grafo[u])
		{
			for (auto it = lista.upper_bound(ant); it != lista.end() && *it < v; )
			{
				fila.push(*it);
				it = lista.erase(it);
			}

			ant = v;
		}

		for (auto it = lista.upper_bound(ant); it != lista.end() && *it <= n; )
		{
			fila.push(*it);
			it = lista.erase(it);
		}
	}
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].insert(v); grafo[v].insert(u);
	}

	for (int i = 1; i <= n; i++)
		lista.insert(i);

	int cc = 0;
	for (int i = 1; i <= n; i++)
		if (lista.find(i) != lista.end())
			++cc, bfs(i);

	printf("%d\n", cc-1);
}
