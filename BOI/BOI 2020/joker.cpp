// BOI 2020 - Joker
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 2e5+10;
 
struct DSU
{
	int pai[maxn], peso[maxn], edge[maxn];
	bool bp;
 
	struct RollBack
	{
		int u, v, pu;
		bool b;
	};
 
	stack<RollBack> stk;
 
	void init(int n)
	{
		bp = 1;
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
 
		stk.push({x, y, peso[x], bp});
 
		if (x == y) return bp = (bp && (cx != cy));
 
		pai[y] = x, peso[x] += peso[y];
		edge[y] = cx ^ cy ^ 1;
 
		return 1;
	}
 
	void rollback(int x)
	{
		while (stk.size() > x)
		{
			auto E = stk.top(); stk.pop();
 
			pai[E.u] = E.u, pai[E.v] = E.v;
			peso[E.u] = E.pu, edge[E.v] = 0;
			bp = E.b;
		}
	}
} dsu;
 
int n, m;
 
int opt[maxn];
pii edge[maxn];
 
void solve(int l, int r)
{
	if (l > r) return;
 
	int mid = (l+r)>>1, s0 = dsu.stk.size();
 
	for (int i = l; i <= mid; i++)
		dsu.Join(edge[i].ff, edge[i].ss);
 
	int s1 = dsu.stk.size();
 
	if (!dsu.bp) opt[mid] = opt[r+1];
	else
	{
		for (int i = opt[r+1]; i >= max(opt[(l == 0 ? 0 : l-1)], mid+1); i--)
		{
			if (!dsu.Join(edge[i].ff, edge[i].ss))
			{
				opt[mid] = i;
				break;
			}
		}
	}
 
	dsu.rollback(s1);
	solve(mid+1, r);
 
	dsu.rollback(s0);
	for (int i = opt[r+1]; i > opt[mid]; i--)
		dsu.Join(edge[i].ff, edge[i].ss);
 
	solve(l, mid-1);
 
	dsu.rollback(s0);
}
 
int main(void)
{
	int q;
	scanf("%d %d %d", &n, &m, &q);
 
	edge[0] = {0, maxn-1};
 
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &edge[i].ff, &edge[i].ss);
	
	edge[m+1] = {0, maxn-1};
 
	dsu.init(n);
 
	opt[0] = 1, opt[m+1] = m+1;
	solve(0, m);
 
	while (q--)
	{
		int l, r;
		scanf("%d %d", &l, &r);
 
		if (opt[l-1] > r) printf("YES\n");
		else printf("NO\n");
	}
}
