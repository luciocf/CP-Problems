// Neps Academy - Liga de Programação 2020 - Etapa 1 - Estradas Espaciais
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 1e5+10;
 
typedef pair<int, int> pii;
 
int in[MAXN], low[MAXN], comp[MAXN], dist[MAXN], t, ans;
bool bridge[MAXN], mark[MAXN];
vector<pii> grafo[MAXN];
vector<int> tree[MAXN];
 
void find_bridge(int u, int p)
{
	in[u] = low[u] = ++t;
 
	for (auto P: grafo[u])
	{
		int v = P.first;
 
		if (v == p) continue;
 
		if (in[v])
		{
			low[u] = min(low[u], in[v]);
			continue;
		}
 
		find_bridge(v, u);
 
		if (low[v] > in[u]) bridge[P.second] = 1, ans++;
 
		low[u] = min(low[u], low[v]);
	}
}
 
void DFS(int u, int c)
{
	comp[u] = c;
 
	for (auto v: grafo[u])
	{
		if (bridge[v.second] || comp[v.first]) continue;
 
		DFS(v.first, c);
	}
}
 
void BFS(int u)
{
	queue<int> fila;
	fila.push(u);
	mark[u] = 1;
 
	while (!fila.empty())
	{
		int x = fila.front();
		fila.pop();
 
		for (auto v: tree[x])
		{
			if (mark[v]) continue;
 
			dist[v] = dist[x]+1, mark[v] = 1;
			fila.push(v);
		}
	}
}
 
int main(void)
{ 
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;

		u++, v++;
		grafo[u].push_back({v, i}); grafo[v].push_back({u, i});
	}

	find_bridge(1, -1);

	int c = 0;
	for (int i = 1; i <= n; i++)
		if (!comp[i])
			DFS(i, ++c);

	for (int i = 1; i <= n; i++)
		for (auto v: grafo[i])
			if (comp[v.first] != comp[i])
				tree[comp[i]].push_back(comp[v.first]);

	BFS(1);

	int maior = 0, s = 1;
	for (int i = 1; i <= c; i++)
		if (dist[i] > maior)
			maior = dist[i], s = i;

	memset(mark, 0, sizeof mark);
	memset(dist, 0, sizeof dist);

	BFS(s);

	maior = 0;
	for (int i = 1; i <= c; i++)
		maior = max(maior, dist[i]);

	cout << maior << "\n";
}
