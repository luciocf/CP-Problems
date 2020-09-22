// IOI 2020 - Stations
// Lúcio Cardoso

// ------------- labels.cpp -------------

#include <bits/stdc++.h>
#include "labels.h"
#include <vector>

using namespace std;

const int maxn = 1e3+10;

static int st[maxn], en[maxn], nivel[maxn], tt;

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;

		dfs(v, u);
	}

	en[u] = ++tt;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v)
{
	tt = -1;
	for (int i = 0; i < n; i++)
		grafo[i].clear();

	for (int i = 0; i < n-1; i++)
	{
		grafo[u[i]].push_back(v[i]);
		grafo[v[i]].push_back(u[i]);
	}

	dfs(0, -1);

	vector<int> num;

	for (int i = 0; i < n; i++)
	{
		if (nivel[i]%2 == 0) num.push_back(st[i]);
		else num.push_back(en[i]);
	}

	map<int, int> mp;

	for (auto x: num)
		mp[x] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (auto &x: num)
		x = mp[x];

	return num;
}

// ------------- stations.cpp -------------

#include <bits/stdc++.h>
#include "stations.h"
#include <vector>

using namespace std;

const int maxn = 1e3+10;

static int st[maxn], en[maxn];

int find_next_station(int u, int v, vector<int> c)
{
	if (c.size() == 1) return c[0];

	bool flag = 0;

	for (auto x: c)
		if (u < x)
			flag = 1;

	if (!flag)
	{
		for (int i = 1; i < c.size()-1; i++)
		{
			st[i] = c[i];
			en[i] = c[i+1]-1;
		}

		st[c.size()-1] = c[c.size()-1];
		en[c.size()-1] = u;

		for (int i = 1; i < c.size(); i++)
			if (v >= st[i] && v <= en[i])
				return c[i];

		return c[0];
	}
	else
	{
		st[0] = u+1;
		en[0] = c[0];

		for (int i = 1; i < c.size()-1; i++)
		{
			en[i] = c[i];
			st[i] = en[i-1]+1;
		}

		for (int i = 0; i < c.size()-1; i++)
			if (v >= st[i] && v <= en[i])
				return c[i];

		return c[c.size()-1];
	}
}	
