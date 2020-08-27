// POI 2010 - Railway
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;
const int inf = 1e9+10;

struct SegmentTree
{
	int tree[2][3*maxn];

	void build(int node, int l, int r)
	{
		tree[0][node] = inf, tree[1][node] = -inf;
		if (l == r) return;

		int mid = (l+r)>>1;

		build(2*node, l, mid); build(2*node+1, mid+1, r);
	}

	void upd(int node, int l, int r, int pos, int v, int q)
	{
		if (l == r)
		{
			tree[q][node] = v;
			return;
		}

		int mid = (l+r)>>1;

		if (pos <= mid) upd(2*node, l, mid, pos, v, q);
		else upd(2*node+1, mid+1, r, pos, v, q);

		tree[0][node] = min(tree[0][2*node], tree[0][2*node+1]);
		tree[1][node] = max(tree[1][2*node], tree[1][2*node+1]); 
	}

	int query(int node, int l, int r, int a, int b, int q)
	{
		if (l > b || r < a) return (q == 0 ? inf : -inf);
		if (l >= a && r <= b) return tree[q][node];

		int mid = (l+r)>>1;

		if (!q) return min(query(2*node, l, mid, a, b, q), query(2*node+1, mid+1, r, a, b, q));
		return max(query(2*node, l, mid, a, b, q), query(2*node+1, mid+1, r, a, b, q));
	}
} seg;

int n;
int a[maxn];
int l[maxn], r[maxn];

int back[maxn];

int cor[maxn];

bool done[maxn], mark[maxn];

void get_range(void)
{
	int at = 1;
	int x = 1;

	for (int i = 1; i <= n; i++)
	{
		while (mark[x]) ++x;

		l[a[i]] = x, mark[x] = 1;
		done[a[i]] = 1;

		while (done[at])
		{
			while (mark[x]) ++x;

			r[at] = x, mark[x] = 1;
			++at;
		}
	}
}

void dfs(int u, int c)
{
	seg.upd(1, 1, 2*n, r[u], inf, 0);
	seg.upd(1, 1, 2*n, l[u], -inf, 1);

	cor[u] = c;

	while (true)
	{
		int x = seg.query(1, 1, 2*n, l[u]+1, r[u]-1, 0);
		if (x >= l[u]) break;

		dfs(back[x], !c);
	}

	while (true)
	{
		int x = seg.query(1, 1, 2*n, l[u]+1, r[u]-1, 1);
		if (x <= r[u]) break;

		dfs(back[x], !c);
	}
}

bool intersect(vector<pii> V)
{
	sort(V.begin(), V.end());

	stack<int> stk;

	for (auto pp: V)
	{
		int l = pp.ff, r = pp.ss;

		while (stk.size() && l > stk.top())
			stk.pop();

		if (stk.size() && stk.top() < r)
			return true;

		stk.push(r);
	}

	return false;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	get_range();
	seg.build(1, 1, 2*n);

	for (int i = 1; i <= n; i++)
	{
		back[l[i]] = back[r[i]] = i;

		seg.upd(1, 1, 2*n, r[i], l[i], 0);
		seg.upd(1, 1, 2*n, l[i], r[i], 1);
	}

	memset(cor, -1, sizeof cor);
	for (int i = 1; i <= n; i++)
		if (cor[i] == -1)
			dfs(i, 0);

	vector<pii> zero, um;

	for (int i = 1; i <= n; i++)
	{	
		if (!cor[i])
			zero.push_back({l[i], r[i]});
		else
			um.push_back({l[i], r[i]});
	}

	if (intersect(um) || intersect(zero)) printf("NIE\n");
	else
	{
		printf("TAK\n");

		for (int i = 1; i <= n; i++)
			printf("%d ", cor[a[i]]+1);
		printf("\n");
	}
}
