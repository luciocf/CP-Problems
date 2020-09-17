#include <bits/stdc++.h>
#include "supertrees.h"
#include <vector>
 
using namespace std;
 
const int maxn = 1e3+10;
 
struct DSU
{
	int pai[maxn], peso[maxn];
 
	void init(int n)
	{
		for (int i = 0; i < n; i++)
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
} dsu;
 
int pai[maxn];
 
bool liga[maxn][maxn];
bool in[maxn];
 
void edge(int u, int v)
{
	liga[u][v] = liga[v][u] = 1;
}
 
int construct(vector<vector<int>> p)
{
	int n = p.size();
	vector<vector<int>> ans;
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (p[i][j] == 3)
				return 0;
 
	dsu.init(n);
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (p[i][j] != 0)
				dsu.Join(i, j);
 
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (dsu.Find(i) == dsu.Find(j) && p[i][j] == 0)
				return 0;
 
	for (int f = 0; f < n; f++)
	{
		vector<int> comp;
 
		for (int j = 0; j < n; j++)
			if (dsu.Find(j) == f)
				comp.push_back(j);
 
		if (comp.size() == 0) continue;
 
		int u = -1, v = -1;
 
		for (auto i: comp)
			for (auto j: comp)
				if (p[i][j] == 2)
					u = i, v = j;
 
		if (u == -1)
		{
			for (auto i = 0; i < comp.size(); i++)
			{
				if (i < (int)comp.size()-1) edge(comp[i], comp[i+1]);
				if (i > 0) edge(comp[i], comp[i-1]);
			}
 
			continue;
		}
 
		vector<int> ciclo;
		ciclo.push_back(u); ciclo.push_back(v);
		in[u] = 1, in[v] = 1;
 
		for (auto i: comp)
		{
			bool ok = 1;
 
			for (auto c: ciclo)
				if (p[i][c] != 2)
					ok = 0;
 
			if (ok)
			{
				ciclo.push_back(i);
				in[i] = 1;
			}
		}
 
		if (ciclo.size() == 2) return 0;
 
		edge(ciclo[0], ciclo.back());
		for (int i = 1; i < ciclo.size(); i++)
			edge(ciclo[i], ciclo[i-1]);
 
		for (auto i: comp)
		{
			if (in[i]) continue;
 
			int ind, qtd = 0;
 
			for (auto c: ciclo)
				if (p[i][c] == 1)
					++qtd, ind = c;
 
			if (qtd > 1) return 0;
 
			pai[i] = ind;
			edge(ind, i);
		}
 
		for (auto i: comp)
		{
			for (auto j: comp)
			{
				if (!in[i] && !in[j])
				{
					if (pai[i] == pai[j] && p[i][j] == 2) return 0;
 
					if (pai[i] != pai[j] && p[i][j] == 1) return 0;
				}
			}
		}
	}
 
	for (int i = 0; i < n; i++)
	{
		vector<int> a;
		a.resize(n);
 
		for (int j = 0; j < n; j++)
			if (liga[i][j])
				a[j] = 1;
 
		ans.push_back(a);
	}
 
	build(ans);
	return 1;
}
