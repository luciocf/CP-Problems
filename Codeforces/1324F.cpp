// Codeforces 1324F - Maximum White Subtree
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 2e5+10;
const int inf = 1e9+10;
 
int cor[maxn];
int sub[maxn];
 
int ans[maxn];
 
vector<int> grafo[maxn];
 
void dfs(int u, int p)
{
	sub[u] = (cor[u] ? 1 : -1);
 
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			dfs(v, u);
 
			if (sub[v] > 0) sub[u] += sub[v];
		}
	}
}
 
void rotate(int u, int p)
{
	if (sub[p] > 0) sub[u] += sub[p];
	ans[u] = sub[u];
 
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			if (sub[v] > 0) sub[u] -= sub[v];
 
			rotate(v, u);
			
			if (sub[v] > 0) sub[u] += sub[v];
		}
	}
 
	if (sub[p] > 0) sub[u] -= sub[p];
}
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &cor[i]);
 
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
 
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
 
	dfs(1, 0);
 
	rotate(1, 0);
 
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
