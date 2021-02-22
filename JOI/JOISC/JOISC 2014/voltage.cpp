// JOISC 2014 - Voltage
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int n, m, C, B;
pii edge[maxn];
bool ans[maxn];

struct DSU
{
	int pai[maxn], peso[maxn], edge[maxn];
	int cc;
	bool bp;

	struct RollBack
	{
		int u, v, pu, c;
		bool b;
	};

	stack<RollBack> stk;

	void init(void)
	{
		bp = 1, cc = n;
		for (int i = 0; i < maxn; i++)
			pai[i] = i, peso[i] = 1;
	}

	int Find(int x, int &c)
	{
		if (pai[x] == x) return x;

		c ^= edge[x];

		return Find(pai[x], c);
	}

	bool Join(int x, int y)
	{
		int cx = 0, cy = 0;
		x = Find(x, cx), y = Find(y, cy);

		if (peso[x] < peso[y])
		{
			swap(x, y);
			swap(cx, cy);
		}

		stk.push({x, y, peso[x], cc, bp});

		if (x == y) return bp = (bp && (cx != cy));

		cc--;
		pai[y] = x, peso[x] += peso[y];
		edge[y] = cx ^ cy ^ 1;

		return 1;
	}

	void rollback(int x)
	{
		while (stk.size() > x)
		{
			auto E = stk.top(); stk.pop();

			peso[E.u] = E.u;
			pai[E.v] = E.v, edge[E.v] = 0;
			cc = E.c, bp = E.b;
		}
	}
} dsu;

void solve(int l, int r)
{
	if (l > r) return;

	int mid = (l+r)>>1;
	int s0 = dsu.stk.size();

	for (int i = r; i >= mid; i--)
		dsu.Join(edge[i].ff, edge[i].ss);

	solve(l, mid-1);

	dsu.rollback(s0);

	for (int i = l; i <= mid; i++)
		dsu.Join(edge[i].ff, edge[i].ss);

	solve(mid+1, r);

	dsu.rollback((int)dsu.stk.size()-1);

	for (int i = mid+1; i <= r; i++)
		dsu.Join(edge[i].ff, edge[i].ss);

	ans[mid] = (dsu.bp && (dsu.cc > C || !B));

	dsu.rollback(s0);
}

int main(void)
{
	scanf("%d %d", &n, &m);

	dsu.init();

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &edge[i].ff, &edge[i].ss);
		dsu.Join(edge[i].ff, edge[i].ss);
	}

	C = dsu.cc, B = dsu.bp;
	dsu.rollback(0);

	solve(1, m);

	int tot = 0;
	for (int i = 1; i <= m; i++)
		if (ans[i])
			++tot;

	printf("%d\n", tot);
}
