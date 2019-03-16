// BOI 2015 - Hacker
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 5e5+10;
const int inf = 1e9+10;
 
int n;
int v[2*maxn];
int tree[4*maxn], lazy[4*maxn];
 
void init(void)
{
	for (int i = 0; i < 4*maxn; i++)
		tree[i] = lazy[i] = inf;
}
 
void flush(int node, int l, int r)
{
	if (lazy[node] == inf) return;
 
	tree[node] = min(tree[node], lazy[node]);
 
	if (l != r)
	{
		lazy[2*node] = min(lazy[2*node], lazy[node]);
		lazy[2*node+1] = min(lazy[2*node+1], lazy[node]);
	}
 
	lazy[node] = inf;
}
 
void upd(int node, int l, int r, int a, int b, int v)
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
 
int query(int node, int l, int r, int pos)
{
	flush(node, l, r);
	if (l == r) return tree[node];
 
	int mid = (l+r)>>1;
 
	if (pos <= mid) return query(2*node, l, mid, pos);
	return query(2*node+1, mid+1, r, pos);
}
 
int main(void)
{
	init();
 
	cin >> n;
 
	int m = (n+1)/2;
 
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		v[n+i] = v[i];
	}
 
	int soma = 0;
	for (int i = 1; i <= m; i++)
		soma += v[i];
 
	upd(1, 1, n, 1, m, soma);
 
	int ans = 0;
	for (int i = m + 1; i-m+1 <= n; i++)
	{
		soma -= v[i-m];
		soma += v[i];
 
		if (i <= n) upd(1, 1, n, i-m+1, i, soma);
		else
		{
			upd(1, 1, n, i-m+1, n, soma);
			upd(1, 1, n, 1, i-n, soma);
		}
	}
 
	for (int i = 1; i <= n; i++) 
		ans = max(ans, query(1, 1, n, i));
 
	cout << ans << "\n";
}
