// COCI 2016/2017 - Sirni
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest6_solutions/solutions.pdf

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
const int maxn = 1e5+10;
const int maxv = 1e7+1;
 
struct DSU
{
	int pai[maxn], peso[maxn];
 
	void init(int n)
	{
		for (int i = 1; i <= n; i++)
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
 
int a[maxn];
int prim[maxv];
int fq[maxn];
 
vector<pii> V[maxv];
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
 
	sort(a+1, a+n+1);
 		
	int tot = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == a[i+1]) continue;
		tot += (a[n]/a[i]);
	}
 
 	int ptr = 2;
	for (int i = a[1]; i <= a[n]; i++)
	{
		while (ptr <= n && a[ptr] < i)
			ptr++;
 
		prim[i] = ptr;
	}
 
 	int m = 0;
	dsu.init(n);
 
	for (int i = 2; i <= n; i++)
		V[a[i]-a[i-1]].push_back({i-1, i});
 
	for (int i = 1; i <= n; i++)
	{
		int j;
		for (j = i; j <= n && a[i] == a[j]; j++)
			if (j != i)
				dsu.Join(i, j), m++;
 
		i = j-1;
			
		for (int v = 2*a[i]; v <= a[n]; v += a[i])
		{
			j = v;
			for (; j <= a[n] && prim[j] == prim[v]; j += a[i])
				;
			j -= a[i];
 
			v = j;
 
			V[a[prim[v]]-v].push_back({i, prim[v]});
		}
	}
 
	ll ans = 0;
 
	for (int w = 0; w < maxv; w++)
	{
		if (m == n-1) break;
 
		for (auto pp: V[w])
		{
			int u = pp.ff, v = pp.ss;
	 
			if (dsu.Find(u) != dsu.Find(v))
			{
				ans += 1ll*w;
				dsu.Join(u, v), ++m;
			}
		}
	}
 
	printf("%lld\n", ans);
}
