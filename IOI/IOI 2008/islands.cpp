// IOI 2008 - Islands
// Lúcio Cardoso

// Solution: https://ioinformatics.org/files/ioi2008solutions.pdf 

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
const int maxn = 1e6+1;
const ll inf = 1e15+10;
 
int n;
 
int peso[maxn];
 
int firstCycle, lastCycle, backEdge;
int pai[maxn], edgePai[maxn];

ll maiorDist;
int indDist;

bitset<maxn> mark, markCycle;
 
vector<pii> grafo[maxn];
 
void findCycle(int u, int p)
{
	mark[u] = 1;
 
	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;
		if (e == p) continue;
 
		if (mark[v])
		{
			firstCycle = u, lastCycle = v;
			backEdge = peso[e];
			continue;
		}
 
		pai[v] = u, edgePai[v] = peso[e];
		findCycle(v, e);
	}
}
 
void dfs(int u, int p, ll dist)
{
	if (dist >= maiorDist) indDist = u;
 
	maiorDist = max(maiorDist, dist);
 
	for (auto pp: grafo[u])
	{
		int v = pp.first, e = pp.second;
		if (v == p || markCycle[v]) continue;
 
		dfs(v, u, dist+1ll*peso[e]);
	}
}
 
int main(void)
{
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
	{
		int u, w;
		scanf("%d %d", &u, &w);
 
		peso[i] = w;
 
		grafo[u].push_back({i, i});
		grafo[i].push_back({u, i});
	}
 
	ll ans = 0;
 
	for (int T = 1; T <= n; T++)
	{
		if (mark[T]) continue;
 
		findCycle(T, 0);
 
		int at = lastCycle;
		ll soma = backEdge;
 
		vector<int> ciclo;
 	
		while (true)
		{
			ciclo.push_back(at);
			markCycle[at] = 1;
 
			if (at == firstCycle) break;
 
			soma += 1ll*edgePai[at];
			at = pai[at];
		}
 
		reverse(ciclo.begin(), ciclo.end());
 
		ll M = 0, diam = 0, pref = 0;

		ll maxi1 = -inf, maxi2 = -inf;
		for (int i = 0; i < ciclo.size(); i++)
		{
			int u = ciclo[i];

			if (i != 0) pref += 1ll*edgePai[u];

			maiorDist = 0;
			dfs(u, 0, 0);
 
			M = max(M, maiorDist+pref + maxi1);
			maxi1 = max(maxi1, maiorDist-pref);
 
			M = max(M, maiorDist-pref + maxi2 + soma);
			maxi2 = max(maxi2, maiorDist+pref);

			markCycle[u] = 0;
			dfs(indDist, 0, 0);
			markCycle[u] = 1;

			diam = max(diam, maiorDist);
		}
 
		ans += max(M, diam);
	}
 
	printf("%lld\n", ans);
}
