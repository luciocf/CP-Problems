// JOI Final Round 2017 - Foehn Phenomena
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 2e5+10;
 
typedef long long ll;
 
struct Node
{
	ll sMaior=0, sMenor=0;
} tree[4*maxn];
 
int n;
int a[maxn];
 
ll bit[maxn];
 
void upd_bit(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += 1ll*v;
}
 
ll soma(int x)
{
	ll ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}
 
void build(int node, int l, int r)
{
	if (l == r)
	{
		if (l < n && a[l] >= a[l+1]) tree[node].sMaior = (a[l]-a[l+1]);
		else if (l < n) tree[node].sMenor = (a[l+1]-a[l]);
 
		return;
	}
 
	int mid = (l+r)>>1;
 
	build(2*node, l, mid); build(2*node+1, mid+1, r);
 
	tree[node].sMaior = tree[2*node].sMaior + tree[2*node+1].sMaior;
	tree[node].sMenor = tree[2*node].sMenor + tree[2*node+1].sMenor;
}
 
void upd(int node, int l, int r, int pos, int op)
{
	if (l == r)
	{
		ll val1 = 1ll*a[l] + soma(l);
		ll val2 = 1ll*a[l+1] + soma(l+1);
 
		if (val1 >= val2)
		{
			if (!op) tree[node].sMaior -= (val1-val2);
			else tree[node].sMaior += (val1-val2);
		}
		else
		{
			if (!op) tree[node].sMenor -= (val2-val1);
			else tree[node].sMenor += (val2-val1);
		}
 
		return;
	}
 
	int mid = (l+r)>>1;
 
	if (pos <= mid) upd(2*node, l, mid, pos, op);
	else upd(2*node+1, mid+1, r, pos, op);
 
	tree[node].sMaior = tree[2*node].sMaior + tree[2*node+1].sMaior;
	tree[node].sMenor = tree[2*node].sMenor + tree[2*node+1].sMenor;
}
 
int main(void)
{
	int q, s, t;
	scanf("%d %d %d %d", &n, &q, &s, &t);
 
	for (int i = 0; i <= n; i++)
		scanf("%d", &a[i]);
 
	build(1, 0, n);
 
	for (int i = 1; i <= q; i++)
	{
		int l, r, d;
		scanf("%d %d %d", &l, &r, &d);
 
		upd(1, 0, n, l-1, 0);
		if (r != n) upd(1, 0, n, r, 0);
 
		upd_bit(l, d); upd_bit(r+1, -d);
 
		upd(1, 0, n, l-1, 1);
		if (r != n) upd(1, 0, n, r, 1);
 
 
		printf("%lld\n", 1ll*t*tree[1].sMaior - 1ll*s*tree[1].sMenor);
	}
}
