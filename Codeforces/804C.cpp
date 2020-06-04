// Codeforces 804C - Ice cream coloring
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e5+10;
 
int ans[maxn];
 
bool mark[maxn];
 
vector<int> S[maxn];
vector<int> grafo[maxn];
 
void dfs(int u, int p)
{
	vector<int> V;
 
	for (auto c: S[u])
	{
		if (!ans[c]) V.push_back(c);
		else mark[ans[c]] = 1;
	}
 
	int x = 1;
	for (auto c: V)
	{
		while (mark[x]) ++x;
 
		ans[c] = x++;
	}
 
	for (auto c: S[u])
		mark[ans[c]] = 0;
 
	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);
}
 
int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
 
	int tot = 0;
 
	for (int i = 1; i <= n; i++)
	{
		int s;
		scanf("%d", &s);
 
		tot = max(tot, s);
 
		while (s--)
		{
			int c;
			scanf("%d", &c);
 
			S[i].push_back(c);
		}
	}
 
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
 
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
 
	dfs(1, 0);
 
	for (int i = 1; i <= m; i++)
		if (!ans[i])
			ans[i] = 1;
 
	printf("%d\n", max(1, tot));
	for (int i = 1; i <= m; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
