// BOI 2015 - Tug of War
// Lúcio Cardoso

// Solution:

// 1. If a participant with strength s_i can be in l_i or r_i, make a graph with edges (l_i, r_i) of weight s_i.
// We want to set the weight in each edge in the graph for either the first or second group.

// 2. If any connected component in the graph is a tree, the answer is No.

// 3. If not, each CC has exactly one cycle, since the amount of edges and vertices is equal (2*n).

// 4. For every vertex in the graph not present in a cycle (i.e a "tree vertex") just set the value of his parent edge
// to belong to his group.

// 5. Aftet that, our graph has only cycles. For each cycle, there are two sums, one of the edges of even index and one for the
// edges of odd index (the index being the order of appearance in the cycle). We can set one of these sums to the first group and
// the other to the second group.

// 6. Then, we can use a knapsack with a bitset to solve the problem, considering each case of the cycles.

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
const int maxn = 6e4+10;
const int add = 10*maxn;
 
typedef pair<int, int> pii;
 
int n, k;
 
int sa, sb;
 
int pai[maxn], edge[maxn];
 
int firstCycle[maxn], lastCycle[maxn], pesoCycle[2][maxn], inCycle[maxn];
int comp[maxn], back[maxn];
 
bitset<1200002> dp;
 
bool mark[maxn];
 
vector<int> V;
 
vector<pair<pii, int>> grafo[maxn];

// finds cycle in each component
void dfs(int u, int ant, int cc)
{
	comp[u] = cc;
 
	for (auto pp: grafo[u])
	{
		int v = pp.ff.ff, w = pp.ff.ss, e = pp.ss;
 
		if (comp[v] == cc)
		{
			if (ant == e) continue;
 
			firstCycle[cc] = u, lastCycle[cc] = v;
			back[cc] = w;
 
			continue;
		}
 
		pai[v] = u, edge[v] = w;
 
		dfs(v, e, cc);
	}
}
 
void markCycle(int cc)
{
	int v = lastCycle[cc];
 
	int s0 = 0, s1 = back[cc];
	bool turn = 0;
 
	while (true)
	{
		inCycle[v] = true;
 
		if (v == firstCycle[cc]) break;
 
		if (!turn) s0 += edge[v];
		else s1 += edge[v];
 
		v = pai[v];
		turn = !turn;
	}
 
	pesoCycle[0][cc] = s0, pesoCycle[1][cc] = s1;
}

// sums the "tree vertices"
void dfs2(int u)
{
	mark[u] = true;
 
	for (auto pp: grafo[u])
	{
		int v = pp.ff.ff, w = pp.ff.ss;
 
		if (mark[v]) continue;
 
		dfs2(v);
 
		if (!inCycle[v])
		{
			if (v <= n) sa += w;
			else sb += w; 
		}
	}
}
 
int main(void)
{
	scanf("%d %d", &n, &k);
 
	int S = 0;
 
	for (int i = 1; i <= 2*n; i++)
	{
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
 
		b += n;
		S += w;
 
		grafo[a].push_back({{b, w}, i});
		grafo[b].push_back({{a, w}, i});
	}
 
	int cc = 0;
	for (int i = 1; i <= 2*n; i++)
	{
		if (comp[i]) continue;
 
		dfs(i, 0, ++cc);
 
		if (firstCycle[cc] == 0)
		{
			printf("NO\n");
			return 0;
		}
	}
 	
 	int soma = 0;
	for (int i = 1; i <= cc; i++)
	{
		markCycle(i);
		dfs2(firstCycle[i]);

		soma += (max(pesoCycle[0][i], pesoCycle[1][i])-min(pesoCycle[0][i], pesoCycle[1][i]));
	}
 	
	dp[sa-sb-soma+add] = 1;
	for (int i = 1; i <= cc; i++)
	{ 
		int ss = 2*(max(pesoCycle[0][i], pesoCycle[1][i])-min(pesoCycle[0][i], pesoCycle[1][i]));
		dp |= (dp << ss);
	}
 
	for (int i = add-k; i <= add+k; i++)
	{
		if (dp[i])
		{
			printf("YES\n");
			return 0;
		}
	}
 
	printf("NO\n");
}
