// Codeforces 1245D - Shichikuji and Power Grid
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e3+10;
const int maxm = 5e6+10;
 
struct Edge
{
	int u, v;
	ll w;
} edge[maxm];
 
int pai[maxn], peso[maxn];
 
int x[maxn], y[maxn], c[maxn], k[maxn];
 
bool comp(Edge a, Edge b)
{
	return a.w < b.w;
}
 
void init(int n)
{
	for (int i = 0; i <= n; i++)
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
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &x[i], &y[i]);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &k[i]);
 
	int m = 0;
 
	for (int i = 1; i <= n; i++)
		edge[++m] = {0, i, c[i]};
 
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			edge[++m] = {i, j, 1ll*(k[i]+k[j])*(abs(x[i]-x[j])+abs(y[i]-y[j]))};
 
	sort(edge+1, edge+m+1, comp);
 
	init(n);
 
	ll ans = 0;
 
	vector<int> station;
	vector<Edge> connect;
 
	for (int i = 1; i <= m; i++)
	{
		if (Find(edge[i].u) != Find(edge[i].v))
		{
			ans += edge[i].w;
			Join(edge[i].u, edge[i].v);
 
			if (edge[i].u == 0)
				station.push_back(edge[i].v);
			else
				connect.push_back(edge[i]);
		}
	}
 
	printf("%lld\n", ans);
 
	printf("%d\n", station.size());
	for (auto u: station)
		printf("%d ", u);
	printf("\n");
	printf("%d\n", connect.size());
	for (auto e: connect)
		printf("%d %d\n", e.u, e.v);
}
