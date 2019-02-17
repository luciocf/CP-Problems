// CEOI 2018 - Global Warming
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 2e5+10;
const int maxv = 2e9+10;
 
struct Node
{
	int v;
	Node *l, *r;
 
	Node()
	{
		v = 0;
		l = r = NULL;
	}
};
 
int n, x;
int num[maxn];
int suf[maxn];
 
int get(Node *t) {return (t ? t->v : 0);}
 
void clear(Node *node, int l, int r)
{
	if (!node) return;
 
	if (l == r)
	{
		node->v = 0;
		return;
	}
 
	int mid = (l+r)>>1;
 
	clear(node->l, l, mid); clear(node->r, mid+1, r);
 
	node->v = 0;
}
 
void upd(Node *node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		node->v = max(v, node->v);
		return;
	}
 
	int mid = (l+r)>>1;
 
	if (pos <= mid)
	{
		if (!node->l) node->l = new Node();
		upd(node->l, l, mid, pos, v);
	}
	else
	{
		if (!node->r) node->r = new Node();
		upd(node->r, mid+1, r, pos, v);
	}
 
	node->v = max(get(node->l), get(node->r));
}
 
int query(Node *node, int l, int r, int a, int b)
{
	if (!node || l > b || r < a) return 0;
	if (l >= a && r <= b) return node->v;
 
	int mid = (l+r)>>1;
 
	int p1 = query(node->l, l, mid, a, b);
	int p2 = query(node->r, mid+1, r, a, b);
 
	return max(p1, p2);
}
 
int main(void)
{
	scanf("%d %d", &n, &x);
 
	Node *t = new Node();
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
 
	for (int i = n; i >= 1; i--)
	{
		int val = query(t, 1, maxv, num[i]+1, maxv);
 
		suf[i] = val+1;
 
		upd(t, 1, maxv, num[i], suf[i]);
	}
 
	int ans = 0;
	t = new Node();
 
	for (int i = 1; i <= n; i++)
	{
		int val = 0;
		if (num[i]+x > 1) val = query(t, 1, maxv, 1, num[i]+x-1);
 
		ans = max(ans, suf[i]+val);

		int p = 0;
		if (num[i] > 1) p = query(t, 1, maxv, 1, num[i]-1);
 
		upd(t, 1, maxv, num[i], p+1);
	}
 
	printf("%d\n", ans);
}
