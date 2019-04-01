// JOI Open Contest 2015 - Election
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e5+10;
 
int n, m;
 
int A[maxn], B[maxn], C[maxn];
 
int nivel[maxn], pai[maxn], sz[maxn];
 
int chain[maxn], head[maxn], pos[maxn];
int cc, pp;
 
int bit[2][maxn];
 
int dp[maxn];
 
vector<int> grafo[maxn], op[maxn];
 
void upd(int x, int v, int t)
{
	for (; x < maxn; x += (x&-x))
		bit[t][x] += v;
}
 
int soma(int x, int t)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[t][x];
	return ans;
}
 
void dfs(int u, int p)
{
	sz[u] = 1;
 
	for (auto v: grafo[u])
	{
		if (v == p) continue;
 
		pai[v] = u, nivel[v] = nivel[u]+1;
 
		dfs(v, u);
 
		sz[u] += sz[v];
	}
}
 
void hld(int u)
{
	if (!head[cc]) head[cc] = u;
	chain[u] = cc, pos[u] = ++pp;
 
	int maior = -1, ind = -1;
	for (auto v: grafo[u])
		if (v != pai[u] && sz[v] > maior)
			maior = sz[v], ind = v;
 
	if (ind != -1) hld(ind);
 
	for (auto v: grafo[u])
		if (v != pai[u] && v != ind)
			cc++, hld(v);
}
 
int lca(int u, int v)
{
	while (chain[u] != chain[v])
	{
		if (nivel[head[chain[u]]] > nivel[head[chain[v]]])
			u = pai[head[chain[u]]];
		else
			v = pai[head[chain[v]]];
	}
 
	if (nivel[u] > nivel[v]) return v;
	return u;
}
 
int query(int u, int v, int t)
{
	int ans = 0;
 
	while (true)
	{
		if (chain[u] == chain[v]) return ans+soma(pos[u], t)-soma(pos[v]-1, t);
 
		ans += soma(pos[u], t)-soma(pos[head[chain[u]]]-1, t);
		u = pai[head[chain[u]]];
	}
}
 
int solve(int u, int p)
{
	int sum = 0;
	for (auto v: grafo[u])
	{
		if (v == p) continue;
 
		solve(v, u);
 
		sum += dp[v];
	}

	upd(pos[u], sum, 0);
 
	dp[u] = sum;
 
	for (auto i: op[u])
	{
		int a = A[i], b = B[i], c = C[i];
		int x = query(a, u, 0) + query(b, u, 0) - sum;

		dp[u] = max(dp[u], c+x-query(a, u, 1)-query(b, u, 1));
	}

	upd(pos[u], dp[u], 1);
}
 
int main(void)
{
	scanf("%d", &n);
 
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
 
		grafo[u].push_back(v); grafo[v].push_back(u);
	}
 
	dfs(1, 0);
	hld(1);
 
	scanf("%d", &m);
 
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &A[i], &B[i], &C[i]);
 
		op[lca(A[i], B[i])].push_back(i);
	}
 
	solve(1, 0);
 
	printf("%d\n", dp[1]);
}
