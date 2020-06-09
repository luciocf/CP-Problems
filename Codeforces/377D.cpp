// CF 377D - Developing Game
// Lúcio Cardoso

// Solution is the same as editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

struct Range
{
	int l, v, r;
} range[maxn];

struct Event
{
	int x, y1, y2;
	int type;
} event[maxn];

pii tree[4*maxn];
int lazy[4*maxn];

bool comp(Event a, Event b)
{
	if (a.x == b.x) return a.type < b.type;
	return a.x < b.x;
}

void flush(int node, int l, int r)
{
	if (!lazy[node]) return;

	if (l != r)
		lazy[2*node] += lazy[node], lazy[2*node+1] += lazy[node];

	tree[node].ff += lazy[node];
	lazy[node] = 0; 
}

void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = {0, l};
		return;
	}

	int mid = (l+r)>>1;

	build(2*node, l, mid); build(2*node+1, mid+1, r);

	tree[node] = max(tree[2*node], tree[2*node+1]);
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

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int m = 0;

	for (int i = 1; i <= n; i++)
	{
		int l, v, r;
		scanf("%d %d %d", &l, &v, &r);

		range[i] = {l, v, r};

		event[++m] = {l, v, r, 0};
		event[++m] = {v, v, r, 1};
	}

	build(1, 1, maxn-1);

	sort(event+1, event+m+1, comp);

	int ans = 0;
	int opt_x = 1, opt_y = 1;

	for (int i = 1; i <= m; i++)
	{
		int x = event[i].x, y1 = event[i].y1, y2 = event[i].y2;

		if (event[i].type == 0)
			upd(1, 1, maxn-1, y1, y2, 1);
		else
			upd(1, 1, maxn-1, y1, y2, -1);

		flush(1, 1, n);
		if (tree[1].ff > ans)
		{
			ans = tree[1].ff;
			opt_x = x, opt_y = tree[1].ss;
		}
	}

	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		if (range[i].l <= opt_x && range[i].v >= opt_x && range[i].r >= opt_y && range[i].v <= opt_y)
			printf("%d ", i);
	printf("\n");
}
