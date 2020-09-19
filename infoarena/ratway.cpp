// Infoarena - Ratway
// Lúcio Cardoso

// Solution is the same as in: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/ratway.cpp

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e6+10;
 
int ind[maxn];
 
bool mark[maxn];
 
vector<int> tour;
 
vector<pii> grafo[maxn], ans;
 
void dfs(int u)
{
	while (ind[u] < grafo[u].size())
	{
		int v = grafo[u][ind[u]].ff, e = grafo[u][ind[u]].ss;
		++ind[u];
 
		if (!mark[e])
		{
			mark[e] = 1;
			dfs(v);
		}
	}
 
	tour.push_back(u);
}
 
int main(void)
{
	freopen("ratway.in", "r", stdin); freopen("ratway.out", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
 
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
 
		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i});
	}
 
	vector<int> lista;
	for (int i = 1; i <= n; i++)
		if (grafo[i].size()&1)
			lista.push_back(i);
 
	if (lista.size()%2)
	{
		grafo[lista.back()].push_back({lista.back(), ++m});
		lista.pop_back();
	}
 
	for (int i = 1; i < lista.size(); i += 2)
	{
		grafo[lista[i]].push_back({lista[i-1], ++m});
		grafo[lista[i-1]].push_back({lista[i], m});
	}
 
	dfs(1);
 
	for (int i = 1; i < tour.size(); i++)
	{
		if (i&1) ans.push_back({tour[i-1], tour[i]});
		else ans.push_back({tour[i], tour[i-1]});
	}
 
	if (m&1) ans.push_back({tour[0], tour[0]});
 
	printf("%d\n", ans.size());
	for (auto e: ans)
		printf("%d %d\n", e.ff, e.ss);
}
