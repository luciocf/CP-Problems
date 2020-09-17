#include <bits/stdc++.h>
#include "tickets.h"
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
typedef long long ll;
 
const int maxn = 1510;
 
int turno[maxn][maxn];
 
int ord[maxn];
int qtd[maxn], ptr_l[maxn], ptr_r[maxn];
 
ll find_maximum(int k, vector<vector<int>> x)
{
	int n = x.size();
	int m = x[0].size();
 
	ll ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			ans -= 1ll*x[i][j];
 
	priority_queue<pair<ll, pii>> fila;
 
	for (int i = 0; i < n; i++)
	{
		memset(turno[i], -1, sizeof turno[i]);
 
		fila.push({1ll*x[i][m-1] + 1ll*x[i][k-1], {i, m-1}});
 
		qtd[i] = 0, ord[i] = i;
		ptr_l[i] = 0, ptr_r[i] = m-1;
	}
 
	for (int t = 0; t < (n*k)/2; t++)
	{
		auto pp = fila.top(); fila.pop();
 
		ans += pp.ff;
 
		qtd[pp.ss.ff]++;
 
		if (qtd[pp.ss.ff] == k) continue;
 
		int c = m-pp.ss.ss+1;
 
		fila.push({1ll*x[pp.ss.ff][pp.ss.ss-1] + 1ll*x[pp.ss.ff][k-c], {pp.ss.ff, pp.ss.ss-1}});
	}
 
	for (int r = 0; r < k; r++)
	{
		sort(ord, ord+n, [&] (int a, int b) {return qtd[a] > qtd[b];});
 
		for (int i = 0; i < n/2; i++)
		{
			int j = ord[i];
 
			turno[j][ptr_r[j]] = r;
			ptr_r[j]--;
			qtd[j]--;
		}
 
		for (int i = n/2; i < n; i++)
		{
			int j = ord[i];
 
			turno[j][ptr_l[j]] = r;
			ptr_l[j]++;
		}
	}
 
	vector<vector<int>> S;
		
	for (int i = 0; i < n; i++)
	{
		vector<int> y;
		y.resize(m);
		
		for (int j = 0; j < m; j++)
			y[j] = turno[i][j];
 
		S.push_back(y);
	}
 
	allocate_tickets(S);
	return ans;
}
