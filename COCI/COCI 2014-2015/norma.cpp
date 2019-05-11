// COCI 2014/2015 - Norma
// Lúcio Cardoso

// Solution is the same as the one presented here: http://hsin.hr/coci/archive/2014_2015/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;
const int mod = 1e9;

typedef long long ll;

struct Node
{
	int L, Max, Min;
	int MaxMin, MaxL, MinL;
	int MaxMinL;
} tree[3*maxn];

struct Lazy
{
	int newL, newMax, newMin;
} lazy[3*maxn];

int a[maxn];

void join(int node)
{
	int l = 2*node, r = 2*node+1;

	tree[node].L = (tree[l].L+tree[r].L)%mod;
	tree[node].Max = (tree[l].Max+tree[r].Max)%mod, tree[node].Min = (tree[l].Min+tree[r].Min)%mod;
	tree[node].MaxMin = (tree[l].MaxMin+tree[r].MaxMin)%mod;
	tree[node].MaxL = (tree[l].MaxL+tree[r].MaxL)%mod, tree[node].MinL = (tree[l].MinL+tree[r].MinL)%mod;
	tree[node].MaxMinL = (tree[l].MaxMinL+tree[r].MaxMinL)%mod;
}

void flush(int node, int l, int r)
{
	int L = lazy[node].newL;
	int Max = lazy[node].newMax;
	int Min = lazy[node].newMin;

	if (l != r)
	{
		if (Max != 0) lazy[2*node].newMax = lazy[2*node+1].newMax = Max;
		if (Min != 0) lazy[2*node].newMin = lazy[2*node+1].newMin = Min;
		if (L != 0)
		{
			lazy[2*node].newL = (lazy[2*node].newL+L)%mod;
			lazy[2*node+1].newL = (lazy[2*node+1].newL+L)%mod;
		}
	}

	if (Max != 0)
	{
		tree[node].Max = (1ll*(r-l+1)*Max)%mod;
		tree[node].MaxMin = (1ll*tree[node].Min*Max)%mod;
		tree[node].MaxL = (1ll*tree[node].L*Max)%mod;
		tree[node].MaxMinL = (1ll*tree[node].MinL*Max)%mod;
	}
	if (Min != 0)
	{
		tree[node].Min = (1ll*(r-l+1)*Min)%mod;
		tree[node].MaxMin = (1ll*tree[node].Max*Min)%mod;
		tree[node].MinL = (1ll*tree[node].L*Min)%mod;
		tree[node].MaxMinL = (1ll*tree[node].MaxL*Min)%mod;
	}
	if (L != 0)
	{
		tree[node].L = (tree[node].L+(1ll*(r-l+1)*L)%mod)%mod;
		tree[node].MaxL = (tree[node].MaxL+(1ll*tree[node].Max*L)%mod)%mod;
		tree[node].MinL = (tree[node].MinL+(1ll*tree[node].Min*L)%mod)%mod;
		tree[node].MaxMinL = (tree[node].MaxMinL+(1ll*tree[node].MaxMin*L)%mod)%mod;
	}

	lazy[node] = {0, 0, 0};
}

void upd(int node, int l, int r, int a, int b, int v, int op)
{
	flush(node, l, r);

	if (l > b || r < a) return;
	if (l >= a && r <= b)
	{
		if (op == 0) lazy[node].newL += v;
		if (op == 1) lazy[node].newMax = v;
		if (op == 2) lazy[node].newMin = v;

		flush(node, l, r);
		return;
	}

	int mid = (l+r)>>1;

	upd(2*node, l, mid, a, b, v, op); upd(2*node+1, mid+1, r, a, b, v, op);

	join(node);
}

ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);

	if (l > b || r < a) return 0ll;
	if (l >= a && r <= b) return tree[node].MaxMinL%mod;

	int mid = (l+r)>>1;

	return (query(2*node, l, mid, a, b)+query(2*node+1, mid+1, r, a, b))%mod;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	stack<pair<int, int>> m1, m2;

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		while (!m1.empty() && m1.top().first <= a[i])
			m1.pop();

		while (!m2.empty() && m2.top().first >= a[i])
			m2.pop();

		int ind1 = (m1.empty() ? 1 : m1.top().second+1);
		m1.push({a[i], i});

		int ind2 = (m2.empty() ? 1 : m2.top().second+1);
		m2.push({a[i], i});

		upd(1, 1, n, ind1, i, a[i], 1);
		upd(1, 1, n, ind2, i, a[i], 2);
		upd(1, 1, n, 1, i, 1, 0);

		ans = (ans+query(1, 1, n, 1, i))%mod;
	}

	printf("%lld\n", ans);
}
