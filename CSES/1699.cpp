// CSES 1699 - Flight Route Requests
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e5+10;
 
int mark[maxn];
 
int comp[maxn];
 
bool bad[maxn];
 
vector<int> grafo[maxn], grafo2[maxn];
 
void dfs(int u, int cc)
{
	mark[u] = 1, comp[u] = cc;
 
	for (auto v: grafo2[u])
		if (!mark[v])
			dfs(v, cc);
}
 
bool find_cycle(int u)
{
	mark[u] = 1;
	bool flag = 0;
 
	for (auto v: grafo[u])
	{
		if (mark[v] == 1) return true;
		if (mark[v] == 0) flag |= find_cycle(v);
	}
 
	mark[u] = 2;
	return flag;
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
 
		grafo2[u].push_back(v); grafo2[v].push_back(u);
	}
 
	int cc = 0;
	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i, ++cc);
 
	memset(mark, 0, sizeof mark);
 
	for (int i = 1; i <= n; i++)
		if (!mark[i])
			bad[comp[i]] |= find_cycle(i);
 
	int ans = n;
	for (int i = 1; i <= cc; i++)
		if (!bad[i])
			ans--;
 
	printf("%d\n", ans);
}
