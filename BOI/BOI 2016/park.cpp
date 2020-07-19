// BOI 2016 - Park
// Lúcio Cardoso

// Solution is the same as in: https://github.com/zoooma13/Competitive-Programming/blob/master/park.cpp

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 3e3+10;
const int maxq = 1e5+10;

struct Query
{
	int r, e, ind;
} qry[maxq];

struct Tree
{
	int x, y, r;
} tree[maxn];

struct Par
{
	int u, v;
	long double k;
} par[maxn*maxn];

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

int n, m, w, h;
bool ans[maxq][5];

bool comp(Query a, Query b) {return a.r < b.r;}
bool comp2(Par a, Par b) {return a.k < b.k;}

long double dist(pii p1, pii p2)
{
	long double d1 = p1.ff-p2.ff, d2 = p1.ss-p2.ss;
	return sqrt(d1*d1 + d2*d2);
}

long double dist_c(int u, int v, int q)
{
	if (q == 0)
	{
		long double d = dist({tree[u].x, tree[u].y}, {tree[v].x, tree[v].y});
		return (d - 1.0*tree[u].r - 1.0*tree[v].r);
	}

	long double d;

	if (v == n+4) d = tree[u].x;
	else if (v == n+1) d = tree[u].y;
	else if (v == n+2) d = w-tree[u].x;
	else d = h-tree[u].y;

	return d-tree[u].r;
}

int main(void)
{
	scanf("%d %d %d %d", &n, &m, &w, &h);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &tree[i].x, &tree[i].y, &tree[i].r);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &qry[i].r, &qry[i].e);
		qry[i].ind = i;
	}

	int at = 0;

	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			par[++at] = {i, j, dist_c(i, j, 0)};

	for (int i = 1; i <= n; i++)
		for (int j = n+1; j <= n+4; j++)
				par[++at] = {i, j, dist_c(i, j, 1)};

	sort(qry+1, qry+m+1, comp);
	sort(par+1, par+at+1, comp2);

	dsu.init(n+4);

	int ptr = 1;

	for (int i = 1; i <= m; i++)
	{
		int R = qry[i].r, ind = qry[i].ind;

		while (ptr <= at)
		{
			if (2.00*R > par[ptr].k) dsu.Join(par[ptr].u, par[ptr].v), ++ptr;
			else break;
		}

		bool lig[5][5];

		for (int j = 1; j <= 4; j++)
			for (int l = 1; l <= 4; l++)
				lig[j][l] = (dsu.Find(n+j) == dsu.Find(n+l));

		if (qry[i].e == 1)
		{
			ans[ind][1] = 1;
			ans[ind][2] = (!lig[1][2] && !lig[1][3] && !lig[1][4]);
			ans[ind][3] = (!lig[2][3] && !lig[2][4] && !lig[1][3] && !lig[1][4]);
			ans[ind][4] = (!lig[1][4] && !lig[2][4] && !lig[3][4]);
		}
		else if (qry[i].e == 2)
		{
			ans[ind][1] = (!lig[1][2] && !lig[1][3] && !lig[1][4]);
			ans[ind][2] = 1;
			ans[ind][3] = (!lig[1][2] && !lig[2][3] && !lig[2][4]);
			ans[ind][4] = (!lig[1][2] && !lig[1][3] && !lig[2][4] && !lig[3][4]);
		}
		else if (qry[i].e == 3)
		{
			ans[ind][1] = (!lig[2][3] && !lig[2][4] && !lig[1][3] && !lig[1][4]);
			ans[ind][2] = (!lig[1][2] && !lig[2][3] && !lig[2][4]);
			ans[ind][3] = 1;
			ans[ind][4] = (!lig[1][3] && !lig[2][3] && !lig[3][4]);
		}
		else
		{
			ans[ind][1] = (!lig[1][4] && !lig[2][4] && !lig[3][4]);
			ans[ind][2] = (!lig[1][2] && !lig[1][3] && !lig[2][4] && !lig[3][4]);
			ans[ind][3] = (!lig[1][3] && !lig[2][3] && !lig[3][4]);
			ans[ind][4] = 1;
		}
	}

	for (int i = 1; i <= m; i++)
	{
		if (ans[i][1]) printf("1");
		if (ans[i][2]) printf("2");
		if (ans[i][3]) printf("3");
		if (ans[i][4]) printf("4");
		printf("\n");
	}
}
