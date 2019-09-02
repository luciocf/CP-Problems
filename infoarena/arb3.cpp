// infoarena - Arb3
// Lúcio Cardoso

// Solution: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/arb3.cpp

#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int, int> pii;
typedef long long ll;
 
const int maxn = 1e5+10;
 
int n;
int a[maxn];
 
int pai[maxn], pos[maxn];
 
vector<pii> grafo[maxn];
vector<ll> pref[maxn];
 
bool comp(pii a, pii b) {return a.first > b.first;}
 
int main(void)
{
	freopen("arb3.in", "r", stdin);
	freopen("arb3.out", "w", stdout);

	int q;
	scanf("%d %d", &n, &q);
 
	for (int i = 2; i <= n; i++)
		scanf("%d", &pai[i]);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
 
	for (int i = 2; i <= n; i++)
		grafo[pai[i]].push_back({a[i], i});
 
	for (int i = 1; i <= n; i++)
	{
		sort(grafo[i].begin(), grafo[i].end(), comp);
 
		for (int j = 0; j < grafo[i].size(); j++)
			pos[grafo[i][j].second] = j+1;
	}
 
	for (int i = 1; i <= n; i++)
	{
		pref[i].push_back(0);
 
		for (int j = 0; j < grafo[i].size(); j++)
			pref[i].push_back(pref[i].back() + 1ll*grafo[i][j].first);
	}
 
	for (int i = 1; i <= q; i++)
	{
		int u;
		ll k;
		scanf("%d %lld", &u, &k);
 
		while (u != 1)
		{
			ll val = 1ll*a[u]-k;

			int p = pai[u];
 
			int ini = pos[u], fim = grafo[p].size()-1, ind = -1;
 
			while (ini <= fim)
			{
				int mid = (ini+fim)>>1;
 
				if (grafo[p][mid].first > val+1) ini = mid+1, ind = mid;  
				else fim = mid-1;
			}
 
			++ind;
 
			k = (pref[p][pos[u]] - 1ll*pos[u]*val);
 
			if (ind)
				k += ((pref[p][ind]-pref[p][pos[u]]) - 1ll*(ind-pos[u])*(val+1));
 
			u = p;
		}
 
		printf("%lld\n", k);
	}
}
