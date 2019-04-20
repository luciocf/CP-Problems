// IOI 2011 - Tropical Garden
// Lúcio Cardoso

// Solution:

/* 1. Duplicate every vertex in the graph to represent the case
   of following its smallest or second smallest edge. The new resulting graph
   will be a functional graph, and therefore has exactly one cycle and 2*N vertices.
   Construct this graph takes O(N) operations.

   2. Calculate the distance d(U, P) from every vertex U to P (in the new graph). It's possible to do that
   by reversing the edges and using a bfs starting from P. If P is in the cycle, a vertex U can reach it in K 
   steps iff d(U, P) <= K and d(U, P) == K (mod C), where C is the cycle's size. Otherwise, if P isn't in the cycle, it is necessary
   that d(U, P) = K.

   3. Repeat step 2 to vertex P', P's duplicated vertex.

   Overral complexity is O(M + N*Q)
*/

#include <bits/stdc++.h>
#include "garden.h"
#include "gardenlib.h"
 
using namespace std;
 
const int maxn = 3e5+10;
 
int grafo[2][maxn];
 
int pai[maxn], nivel[maxn], dist[2][maxn];
int sz1, sz2;
 
bool comp[maxn];
bool mark[maxn], mark2[maxn], inCycle[maxn];
 
vector<int> rev[maxn];
 
void makeGraph(int N)
{
	for (int i = 0; i < N; i++)
	{
		int u = grafo[0][i], v = grafo[1][i];
 
		if (v == -1)
		{
			if (grafo[0][u] == i) pai[i] = u+N;
			else pai[i] = u;

			continue;
		}
 
		if (grafo[0][u] == i && grafo[1][u] != -1) pai[i] = u+N;
		else pai[i] = u;
 
		if (grafo[0][v] == i && grafo[1][v] != -1) pai[i+N] = v+N;
		else pai[i+N] = v;
	}

	for (int i = 0; i < 2*N; i++)
		if (pai[i] != -1)
			rev[pai[i]].push_back(i);
}
 
int getRoot(int u)
{
	mark[u] = true;
 	
 	return (mark[pai[u]] ? u : getRoot(pai[u]));
}
 
void dfs(int u, int cc)
{
	mark2[u] = true, comp[u] = cc;
 
	for (auto v: rev[u])
	{
		if (mark2[v]) continue;
 
		nivel[v] = nivel[u]+1;
		dfs(v, cc);
	}
}

void markCycle(int u, int fim)
{
	inCycle[u] = true;

	if (u != fim) markCycle(pai[u], fim);
}

void findCycle(int N, int P)
{
	int ini1 = -1, fim1 = -1;
	int ini2 = -1, fim2 = -1;

	for (int i = 0; i < 2*N; i++)
	{
		if (comp[i] == comp[P] && nivel[pai[i]] > nivel[i])
			ini1 = pai[i], fim1 = i, sz1 = nivel[pai[i]]-nivel[i]+1;
 
		if (comp[i] == comp[P+N] && nivel[pai[i]] > nivel[i])
			ini2 = pai[i], fim2 = i, sz2 = nivel[pai[i]]-nivel[i]+1;
	}
 
	if (ini1 != -1) markCycle(ini1, fim1); 
	if (ini2 != -1) markCycle(ini2, fim2);
}
 
void bfs(int u, bool q)
{
	memset(mark, 0, sizeof mark);
 
	queue<int> fila;
 
	fila.push(u), dist[q][u] = 0;
 
	while (!fila.empty())
	{
		int u = fila.front();
		fila.pop();
 
		for (auto v: rev[u])
		{
			if (!mark[v])
			{
				fila.push(v), mark[v] = 1;
				dist[q][v] = dist[q][u]+1;
			}
		}
	}
}
 
bool check(int i, int P, int K, bool q)
{
	int sz = (q ? sz1 : sz2);
 
	if ((inCycle[P] && inCycle[i]) || (inCycle[P] && !inCycle[i]))
	{
		int d = dist[q][i];
		if (d <= K && K%sz == d%sz) return true;
	}
	else if (dist[q][i] != -1 && !inCycle[P] && !inCycle[i])
	{
		int d = dist[q][i];
		if (d == K) return true;
	}
 
	return false;
}
 
void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
{
	memset(pai, -1, sizeof pai);
	memset(grafo, -1, sizeof grafo);
	memset(dist, -1, sizeof dist);
 
	for (int i = 0; i < M; i++)
	{
		int u = R[i][0], v = R[i][1];
 
		if (grafo[0][u] == -1) grafo[0][u] = v;
		else if (grafo[1][u] == -1) grafo[1][u] = v;
 
		if (grafo[0][v] == -1) grafo[0][v] = u;
		else if (grafo[1][v] == -1) grafo[1][v] = u;
	}
 
	makeGraph(N);

	int r = getRoot(P);
	dfs(r, 1);

	if (!mark2[P+N])
	{
		r = getRoot(P+N);
		dfs(r, 0);
	}

	findCycle(N, P);
 
	bfs(P, 1);
	bfs(P+N, 0);
 
	for (int q = 0; q < Q; q++)
	{
		int K = G[q], ans = 0;
 
		for (int i = 0; i < N; i++)
		{
			if (comp[i] == comp[P] && check(i, P, K, 1)) ans++;
			else if (comp[i] == comp[P+N] && check(i, P+N, K, 0)) ans++;
		}
 
		answer(ans);
	}
}
