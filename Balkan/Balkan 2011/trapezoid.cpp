// Balkan OI 2011 - Trapezoid
// Lúcio Cardoso

// Solution is the same as: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Trapezoid/main.cpp

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 4e5+10;
const int mod = 30013;

struct Trapezio
{
	int a, b, c, d;
} t[maxn];

int dp_mx[maxn], dp_tot[maxn];

pii tree[4*maxn];

vector<int> st[maxn];

bool comp(Trapezio a, Trapezio b) {return a.d < b.d;}

void upd(int node, int l, int r, int pos, int x, int y)
{
	if (l == r)
	{
		if (x == tree[node].ff)
			tree[node] = {x, (y + tree[node].ss)%mod};

		if (x > tree[node].ff)
			tree[node] = {x, y};

		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, x, y);
	else upd(2*node+1, mid+1, r, pos, x, y);

	tree[node].ff = max(tree[2*node].ff, tree[2*node+1].ff);
	tree[node].ss = 0;

	if (tree[2*node].ff == tree[node].ff) tree[node].ss = (tree[node].ss + tree[2*node].ss)%mod;
	if (tree[2*node+1].ff == tree[node].ff) tree[node].ss = (tree[node].ss + tree[2*node+1].ss)%mod;
}

int query_mx(int node, int l, int r, int a, int b)
{
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return tree[node].ff;

	int mid = (l+r)>>1;

	return max(query_mx(2*node, l, mid, a, b), query_mx(2*node+1, mid+1, r, a, b));
}

int query_tot(int node, int l, int r, int a, int b, int mx)
{
	if (l > b || r < a) return 0;

	if (l >= a && r <= b)
	{
		if (tree[node].ff != mx) return 0;
		return tree[node].ss;
	}

	int mid = (l+r)>>1;

	return (query_tot(2*node, l, mid, a, b, mx) + query_tot(2*node+1, mid+1, r, a, b, mx))%mod;
}

void compress(int n)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
	{
		mp[t[i].a] = 0; mp[t[i].b] = 0;
		mp[t[i].c] = 0; mp[t[i].d] = 0;
	}

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		t[i].a = mp[t[i].a], t[i].b = mp[t[i].b];
		t[i].c = mp[t[i].c], t[i].d = mp[t[i].d];
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d %d", &t[i].a, &t[i].b, &t[i].c, &t[i].d);

	compress(n);

	sort(t+1, t+n+1, comp);

	for (int i = 1; i <= n; i++)
		st[t[i].c].push_back(i);

	upd(1, 1, maxn-1, maxn-1, 0, 1);
	dp_mx[n] = dp_tot[n] = 1;

	for (int i = n-1; i >= 1; i--)
	{
		for (int j = t[i+1].d; j > t[i].d; j--)
			for (auto ind: st[j])
				upd(1, 1, maxn-1, t[ind].a, dp_mx[ind], dp_tot[ind]);

		dp_mx[i] = 1 + query_mx(1, 1, maxn-1, t[i].b+1, maxn-1);
		dp_tot[i] = query_tot(1, 1, maxn-1, t[i].b+1, maxn-1, dp_mx[i]-1);
	}

	int mx = 0;
	for (int i = 1; i <= n; i++)
		mx = max(mx, dp_mx[i]);

	int tot = 0;
	for (int i = 1; i <= n; i++)
		if (dp_mx[i] == mx)
			tot = (tot + dp_tot[i])%mod;

	printf("%d %d\n", mx, tot);
}
