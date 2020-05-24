// Neps Academy - Liga de Programação 2020 - Etapa 2 - Redução Bitwise
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int inf = 2147483647;

struct Node
{
	int Mx, Xor, Or, And, Mn;
} tree[4*maxn];

int n;
int a[maxn];

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node].Mx = tree[node].Xor = tree[node].Or = tree[node].And = tree[node].Mn = a[l];
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node].Mx = max(tree[2*node].Mx, tree[2*node+1].Mx);
	tree[node].Xor = (tree[2*node].Xor ^ tree[2*node+1].Xor);
	tree[node].Or = (tree[2*node].Or | tree[2*node+1].Or);
	tree[node].And = (tree[2*node].And & tree[2*node+1].And);
	tree[node].Mn = min(tree[2*node].Mn, tree[2*node+1].Mn);
}

void upd(int node, int l, int r, int pos, int v)
{
	if (l == r)
	{
		tree[node].Mx = tree[node].Xor = tree[node].Or = tree[node].And = tree[node].Mn = v;
		return;
	}

	int mid = (l+r)>>1;

	if (pos <= mid) upd(2*node, l, mid, pos, v);
	else upd(2*node+1, mid+1, r, pos, v);

	tree[node].Mx = max(tree[2*node].Mx, tree[2*node+1].Mx);
	tree[node].Xor = (tree[2*node].Xor ^ tree[2*node+1].Xor);
	tree[node].Or = (tree[2*node].Or | tree[2*node+1].Or);
	tree[node].And = (tree[2*node].And & tree[2*node+1].And);
	tree[node].Mn = min(tree[2*node].Mn, tree[2*node+1].Mn);
}

int query(int node, int l, int r, int a, int b, int type)
{
	if (a > b || l > b || r < a)
	{
		if (type == 4 || type == 5) return inf;
		return 0;
	}

	if (l >= a && r <= b)
	{
		if (type == 1) return tree[node].Mx;
		if (type == 2) return tree[node].Xor;
		if (type == 3) return tree[node].Or;
		if (type == 4) return tree[node].And;
		if (type == 5) return tree[node].Mn;
	}

	int mid = (l+r)>>1;

	int p1 = query(2*node, l, mid, a, b, type);
	int p2 = query(2*node+1, mid+1, r, a, b, type);

	if (type == 1) return max(p1, p2);
	if (type == 2) return (p1^p2);
	if (type == 3) return (p1|p2);
	if (type == 4) return (p1&p2);
	if (type == 5) return min(p1, p2);
}

int query_pos_mn(int node, int l, int r, int pos, int v)
{
	if (tree[node].Mn > v || r < pos) return -1;
	if (l == r)
	{
		if (tree[node].Mn == v) return l;
		return -1;
	}

	int mid = (l+r)>>1;

	int p1 = query_pos_mn(2*node, l, mid, pos, v);

	if (p1 != -1) return p1;
	return query_pos_mn(2*node+1, mid+1, r, pos, v);
}

int query_pos_mx(int node, int l, int r, int pos, int v)
{
	if (tree[node].Mx < v || r < pos) return -1;
	if (l == r)
	{
		if (tree[node].Mx == v) return l;
		return -1;
	}

	int mid = (l+r)>>1;

	int p1 = query_pos_mx(2*node, l, mid, pos, v);

	if (p1 != -1) return p1;
	return query_pos_mx(2*node+1, mid+1, r, pos, v);
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);


	build(1, 1, n);

	while (q--)
	{
		char c;
		int l, r;
		scanf(" %c %d %d", &c, &l, &r);

		if (c == 'x')
		{
			if (query(1, 1, n, l, r, 2) == 0) printf("%d\n", query(1, 1, n, l, r, 1));
			else printf("-1\n");
		}
		else if (c == 'a')
		{
			if (query(1, 1, n, l, r, 4) == query(1, 1, n, l, r, 5))
			{
				int x = query(1, 1, n, l, r, 5);

				int pos = query_pos_mn(1, 1, n, l, x);

				if ((query(1, 1, n, l, pos-1, 4)&query(1, 1, n, pos+1, r, 4)) == x) printf("%d\n", x);
				else printf("-1\n");
			}
			else printf("-1\n");
		}
		else if (c == 'o')
		{
			if (query(1, 1, n, l, r, 3) == query(1, 1, n, l, r, 1))
			{
				int x = query(1, 1, n, l, r, 1);

				int pos = query_pos_mx(1, 1, n, l, x);
				
				if ((query(1, 1, n, l, pos-1, 3)|query(1, 1, n, pos+1, r, 3)) == x) printf("%d\n", x);
				else printf("-1\n");
			}
			else printf("-1\n");
		}
		else upd(1, 1, n, l, r);
	}
}
