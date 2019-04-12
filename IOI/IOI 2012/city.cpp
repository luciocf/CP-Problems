// IOI 2012 - Ideal City
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e5+10;
const int mod = 1e9;

typedef pair<int, int> pii;

int n, ans;
pii pt[maxn];

// ----- TREES STUFF ------
int vert[maxn], A[maxn];

vector<int> grafo[maxn];

map<pii, int> ind, conecta;
// ------------------------

// -------- DFS STUFF ---------
int S[maxn], W[maxn];
// ----------------------------

bool comp(pii a, pii b)
{
	if (a.ss == b.ss) return a.ff < b.ff;
	return a.ss < b.ss; 
}

void init()
{
	ind.clear(); conecta.clear();
	memset(W, 0, sizeof W); memset(S, 0, sizeof S);

	for (int i = 1; i <= n; i++)
		grafo[i].clear(), A[i] = 0;
}

void make_tree1(void)
{
	sort(pt+1, pt+n+1);
	for (int i = 1; i <= n; i++)
		ind[pt[i]] = i;

	int atual = 1;
	vert[1] = 1, A[1] = 1;

	for (int i = 2; i <= n; i++)
	{
		if (pt[i].ff > pt[i-1].ff || pt[i].ss-pt[i-1].ss > 1)
		{
			vert[i] = ++atual;
			A[atual]++;
			continue;
		}

		vert[i] = atual;
		A[atual]++;
	}

	for (int i = 1; i <= n; i++)
	{
		if (ind.find({pt[i].ff-1, pt[i].ss}) != ind.end())
		{
			int u = i, v = ind[{pt[i].ff-1, pt[i].ss}];
			u = vert[u], v = vert[v];

			if (!conecta[{u, v}])
			{
				conecta[{u, v}] = conecta[{v, u}] = 1;
				grafo[u].push_back(v), grafo[v].push_back(u);
			}
		}
	}
}

void make_tree2(void)
{
	sort(pt+1, pt+n+1, comp);
	for (int i = 1; i <= n; i++)
		ind[pt[i]] = i;

	int atual = 1;
	vert[1] = 1, A[1] = 1; 

	for (int i = 2; i <= n; i++)
	{
		if (pt[i].ss > pt[i-1].ss || pt[i].ff-pt[i-1].ff > 1)
		{
			vert[i] = ++atual;
			A[atual]++;
			continue;
		}

		vert[i] = atual;
		A[atual]++;
	}

	for (int i = 1; i <= n; i++)
	{
		if (ind.find({pt[i].ff, pt[i].ss-1}) != ind.end())
		{
			int u = i, v = ind[{pt[i].ff, pt[i].ss-1}];
			u = vert[u], v = vert[v];

			if (!conecta[{u, v}])
			{
				conecta[{u, v}] = conecta[{v, u}] = 1;
				grafo[u].push_back(v), grafo[v].push_back(u);
			}
		}
	}
}

void dfs(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		int sub = (W[v]+S[v])%mod;
		long long mult = (1ll*W[u]*S[v] + 1ll*sub*S[u])%mod;

		ans = (ans+(1ll*sub*A[u])%mod)%mod;
		ans = (ans+mult)%mod;

		W[u] = (W[u]+sub)%mod;
		S[u] = (S[u]+S[v])%mod;
	}

	S[u] = (S[u]+A[u])%mod;
}

int DistanceSum(int N, int *X, int *Y)
{
	n = N;
	for (int i = 1; i <= n; i++)
		pt[i] = {X[i-1], Y[i-1]};

	make_tree1();
	dfs(1, 0);

	init();

	make_tree2();
	dfs(1, 0);

	return ans;
}
