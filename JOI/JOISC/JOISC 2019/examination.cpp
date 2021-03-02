// JOISC 2019 - Examination
// Lúcio Cardoso

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 2e5+10;
 
struct Node
{
	int v;
	Node *l, *r;
 
	Node()
	{
		l = r = NULL;
		v = 0;
	}
};
 
struct SegmentTree
{
	Node *root;
 
	int get(Node *node)
	{
		return (node ? node->v : 0);
	}
 
	void upd(Node *node, int l, int r, int pos)
	{
		if (l == r)
		{
			node->v++;
			return;
		}
 
		int mid = (l+r)>>1;
 
		if (pos <= mid)
		{
			if (!node->l) node->l = new Node();
			upd(node->l, l, mid, pos);
		}
		else
		{
			if (!node->r) node->r = new Node();
			upd(node->r, mid+1, r, pos);
		}
 
		node->v = get(node->l) + get(node->r);
	}
 
	int query(Node *node, int l, int r, int a, int b)
	{
		if (!node || l > b || r < a) return 0;
		if (l >= a && r <= b) return node->v;
 
		int mid = (l+r)>>1;
 
		return query(node->l, l, mid, a, b) + query(node->r, mid+1, r, a, b);
	}
};
 
struct BIT
{
	SegmentTree bit[maxn];
 
	void upd(int x, int y)
	{
		for (; x < maxn; x += (x&-x))
		{
			if (!bit[x].root) bit[x].root = new Node();
			bit[x].upd(bit[x].root, 1, maxn-1, y);
		}
	}
 
	int soma(int x, int y)
	{
		int ans = 0;
 
		for (; x > 0; x -= (x&-x))
			ans += bit[x].query(bit[x].root, 1, maxn-1, 1, y);
 
		return ans;
	}
} BIT;
 
struct Query
{
	int x, y, z, ind;
} query[maxn];
 
pii a[maxn];
int ans[maxn];
 
int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);
 
	map<int, int> mpx, mpy;
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &a[i].ff, &a[i].ss);
 
		mpx[a[i].ff] = 0;
		mpy[a[i].ss] = 0;
	}
 
	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d %d", &query[i].x, &query[i].y, &query[i].z);
		query[i].ind = i;
 
		mpx[query[i].x] = 0;
		mpy[query[i].y] = 0;
	}
 
	int aux = 0;
	for (auto &x: mpx)
		x.second = ++aux;
 
	aux = 0;
	for (auto &x: mpy)
		x.second = ++aux;
 
	sort(a+1, a+n+1, [&] (pii a, pii b) {return a.ff+a.ss > b.ff+b.ss;});
	sort(query+1, query+q+1, [&] (Query a, Query b) {return a.z > b.z;});
 
	int ptr = 1;
 
	for (int i = 1; i <= q; i++)
	{
		while (ptr <= n && a[ptr].ff+a[ptr].ss >= query[i].z)
		{
			BIT.upd(maxn-mpx[a[ptr].ff], maxn-mpy[a[ptr].ss]);
			ptr++;
		}
 
		ans[query[i].ind] = BIT.soma(maxn-mpx[query[i].x], maxn-mpy[query[i].y]);
	}
 
	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
