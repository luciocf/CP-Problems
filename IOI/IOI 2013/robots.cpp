// IOI 2013 - Robots
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "robots.h"
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e6+10;
 
int n, m, t;
int x[maxn], y[maxn];
 
pii toy[maxn], toy2[maxn];
 
bool mark[maxn];
 
int ind[maxn], sz[maxn];
vector<pii> st[50010];
 
bool ok(int k)
{
	for (int i = 1; i <= n; i++)
		st[i].clear(), sz[i] = 0;
 
	for (int i = 1; i <= t; i++)
		mark[i] = 0;
 
	int ptr = n;
 
	for (int i = t; i >= 1; i--)
	{
		if (sz[ptr] == k) ptr--;
		if (ptr == 0) break;
		if (x[ptr] < toy[i].ff) continue;
 
		mark[i] = 1;
		st[ptr].push_back({toy[i].ss, i}), sz[ptr]++;
	}
 
	for (int i = 1; i <= n; i++)
	{
		ind[i] = 0;
		sort(st[i].begin(), st[i].end());
	}
 
	priority_queue<pii> pq;
	set<pii> candidatos;
 
	for (int i = 1; i <= t; i++)
		if (!mark[i])
			pq.push({toy[i].ss, i});
 
	for (int i = 1; i <= n; i++)
		candidatos.insert({x[i], i});
 
	while (!pq.empty())
	{
		int i = pq.top().ss;
 
		auto it = candidatos.lower_bound({toy[i].ff, 0});
		if (it == candidatos.end())
		{
			pq.pop();
			continue;
		}
 
		int j = it->ss;
 
		if (ind[j] == st[j].size() || st[j][ind[j]].ff >= toy[i].ss)
		{
			candidatos.erase({x[j], j});
			continue;
		}
 
		pq.pop();
 
		if (sz[j] == k)
		{
			mark[st[j][ind[j]].ss] = 0;
 
			pq.push(st[j][ind[j]]);
 
			ind[j]++;
		}
		else sz[j]++;
 
		mark[i] = 1;
	}
 
	ptr = m;
	int qtd = 0;
 
	for (int i = t; i >= 1; i--)
	{
		if (mark[toy2[i].ss]) continue;
 
		if (qtd == k) ptr--, qtd = 0;
		if (ptr == 0 || y[ptr] < toy2[i].ff) return 0;
		
		qtd++;	
	}
 
	return 1;
}
 
int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[])
{
    n = A, m = B, t = T;
 
    for (int i = 0; i < n; i++)
    	x[i+1] = X[i]-1;
 
    for (int i = 0; i < m; i++)
    	y[i+1] = Y[i]-1;
 
    for (int i = 0; i < t; i++)
    	toy[i+1] = {W[i], S[i]};
 
    sort(x+1, x+n+1); sort(y+1, y+m+1); sort(toy+1, toy+t+1);
 
    for (int i = 1; i <= t; i++)
    	toy2[i] = {toy[i].ss, i};
 
    sort(toy2+1, toy2+t+1);
 
    int ini = 1, fim = t, ans = -1;
 
    while (ini <= fim)
    {
    	int mid = (ini+fim)>>1;
 
    	if (ok(mid)) ans = mid, fim = mid-1;
    	else ini = mid+1;
    }
 
    return ans;
}
