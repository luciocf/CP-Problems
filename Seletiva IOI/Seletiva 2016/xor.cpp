// Seletiva IOI 2016 - Xor
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

struct Node
{
	Node *l, *r;
	int mn, mx;

	Node()
	{
		l = r = NULL;
		mn = maxn, mx = -1;
	}
};

int n, k;
int a[maxn];

int L[maxn];
int tree[4*maxn], lazy[4*maxn];

vector<int> pos[maxn];

void add(Node *t, int x, int ind)
{
	for (int i = 30; i >= 0; i--)
	{
		if (x&(1<<i))
		{
			if (!t->r) t->r = new Node();
			t = t->r;
		}
		else
		{
			if (!t->l) t->l = new Node();

			t = t->l;
		}

		t->mn = min(t->mn, ind);
		t->mx = max(t->mx, ind);
	}
}

int get(Node *t, int x, bool q)
{
	int ans = (!q ? maxn : -1);

	for (int i = 30; i >= 0; i--)
	{
		if (!t) return ans;

		if (!(x&(1<<i)))
		{
			if (!(k&(1<<i))) t = t->l;
			else
			{
				if (t->l)
				{
					if (!q) ans = min(ans, t->l->mn);
					else ans = max(ans, t->l->mx);
				}

				t = t->r;
			}
		}
		else
		{
			if (!(k&(1<<i))) t = t->r;
			else
			{
				if (t->r)
				{
					if (!q) ans = min(ans, t->r->mn);
					else ans = max(ans, t->r->mx);
				}

				t = t->l;
			} 
		}
	}

	return ans;
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
		lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

	tree[node] += lazy[node];
	lazy[node] = 0;
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

int get_first(int node, int l, int r, int pos)
{
	flush(node, l, r);
	if (l == r)
	{
		if (!tree[node] && l <= pos) return l;
		return -1;
	}

	int mid = (l+r)>>1;

	flush(2*node, l, mid); flush(2*node+1, mid+1, r);

	if (tree[2*node] == 0) return get_first(2*node, l, mid, pos);
	return get_first(2*node+1, mid+1, r, pos);
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	Node *t1 = new Node();

	for (int i = 1; i <= n; i++)
	{
		int last = get(t1, a[i], 1);

		if (last == maxn) L[i] = -1;
		else L[i] = last;

		add(t1, a[i], i);
	}

	Node *t2 = new Node();

	for (int i = n; i >= 1; i--)
	{
		int last = get(t2, a[i], 0);

		if (last != maxn) pos[last].push_back(i);

		add(t2, a[i], i);
	}

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		if (L[i] == -1) upd(1, 1, n, 1, i, 1);
		else upd(1, 1, n, L[i]+1, i, 1);

		for (auto p: pos[i])
		{
			if (L[p] == -1) upd(1, 1, n, 1, p, -1);
			else upd(1, 1, n, L[p]+1, p, -1);

			L[p] = maxn;
		}

		int primeiro = get_first(1, 1, n, i);

		if (primeiro != -1) ans = max(ans, i-primeiro+1);
	}

	printf("%d\n", ans);
}
