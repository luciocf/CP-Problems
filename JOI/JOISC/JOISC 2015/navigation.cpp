// JOI Spring Camp 2015 - Navigation
// Lúcio Cardoso

// Solution: https://ivaniscoding.wordpress.com/2018/08/25/communication-2-navigation/

// ------------ Code for Anna.cpp ------------

#include <bits/stdc++.h>
#include "Annalib.h"

using namespace std;

const int maxn = 1e5+10;

static vector<int> grafo[maxn];

static int V[maxn];

static void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		if (V[u] == 0)
		{
			if (u > v) V[v] = 0;
			else V[v] = 1;
		}
		else
		{
			if (u > v) V[v] = 1;
			else V[v] = 0;
		}

		dfs(v, u);
	}
}

void Anna(int K, int N, int T, int A[], int B[])
{
	for (int i = 0; i < N-1; i++)
	{
		grafo[A[i]].push_back(B[i]);
		grafo[B[i]].push_back(A[i]);
	}

	V[T] = 0;
	dfs(T, 0);

	for (int i = 1; i <= N; i++)
		Flag(i, V[i]);
}

// ------------ Code for Bruno.cpp ------------

#include <bits/stdc++.h>
#include "Brunolib.h"

using namespace std;

void Bruno(int K, int S, int F, int L, int P[], int Q[])
{
	for (int i = 0; i < L; i++)
	{
		if (F == 0)
		{
			if (Q[i] == 0 && P[i] > S)
			{
				Answer(P[i]);
				return;
			}

			if (Q[i] == 1 && P[i] < S)
			{
				Answer(P[i]);
				return;
			}
		}
		else
		{
			if (Q[i] == 1 && P[i] > S)
			{
				Answer(P[i]);
				return;
			}

			if (Q[i] == 0 && P[i] < S)
			{
				Answer(P[i]);
				return;
			}
		}
	}

	Answer(S);
}

