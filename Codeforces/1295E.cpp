// Codeforces 1295E - Permutation Separation
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
const ll inf = 1e18+10;
 
int n;
int a[maxn], w[maxn];

ll pref[maxn];
 
ll tree[4*maxn], lazy[4*maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = pref[l];
		return;
	}
 
	int mid = (l+r)>>1;
 
	build(2*node, l, mid); build(2*node+1, mid+1, r);
 
	tree[node] = min(tree[2*node], tree[2*node+1]);
}
 
void flush(int node, int l, int r)
{
	if (!lazy[node]) return;
 
	if (l != r)
	{
		lazy[2*node] += lazy[node];
		lazy[2*node+1] += lazy[node];
	}
 
	tree[node] += lazy[node];
	lazy[node] = 0;
}
 
void upd(int node, int l, int r, int a, int b, ll v)
{
	flush(node, l, r);
	if (l > b || r < a) return;
 
	if (l >= a && r <= b)
	{
		lazy[node] = v;
		flush(node, l, r);
		return;
	}
 
	int mid = (l+r)>>1;
 
	upd(2*node, l, mid, a, b, v); upd(2*node+1, mid+1, r, a, b, v);
 
	tree[node] = min(tree[2*node], tree[2*node+1]);
}
 
ll query(int node, int l, int r, int a, int b)
{
	flush(node, l, r);
	if (l > b || r < a) return inf;
	if (l >= a && r <= b) return tree[node];
 
	int mid = (l+r)>>1;
 
	return min(query(2*node, l, mid, a, b), query(2*node+1, mid+1, r, a, b));
}
 
int main(void)
{
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
 
	for (int i = 1; i <= n; i++)
		pref[a[i]] = w[i];
	for (int i = 1; i <= n; i++)
		pref[i] += pref[i-1];
 
	build(1, 1, n);
 
	ll ans = min(w[1], w[n]);
 	
 	ll soma = 0;

	for (int i = 1; i < n; i++)
	{
		soma += 1ll*w[i];
 
		upd(1, 1, n, a[i], n, -2ll*w[i]);
 
		ans = min(ans, query(1, 1, n, a[i], n) + soma);
	}
 
	printf("%lld\n", ans);
}
