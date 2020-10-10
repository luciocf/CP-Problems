// Codeforces 1132G - Greedy Subsequences
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+10;
const int inf = 1e9+10;

struct SegmentTree
{
	int tree[3*maxn], lazy[3*maxn];

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
} seg;

int n;
int a[maxn];

int st[maxn], en[maxn], tt;

int pai[maxn];
vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);

	en[u] = tt;
}

void add(int u)
{
	seg.upd(1, 1, n, st[u], en[u], 1);
}

void rem(int u)
{
	seg.upd(1, 1, n, st[u], st[u], -inf);
}

int get(void)
{
	seg.flush(1, 1, n);
	return seg.tree[1];
}

int main(void)
{
	int k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	stack<pii> stk;

	for (int i = n; i >= 1; i--)
	{
		while (stk.size() && stk.top().ff <= a[i])
			stk.pop();

		if (stk.size())
		{
			pai[i] = stk.top().ss;
			grafo[stk.top().ss].push_back(i);
		}

		stk.push({a[i], i});
	}

	for (int i = 1; i <= n; i++)
		if (!pai[i])
			dfs(i, 0);

	for (int i = 1; i <= k; i++)
		add(i);

	printf("%d", get());

	for (int i = k+1; i <= n; i++)
	{
		rem(i-k);
		add(i);

		printf(" %d", get());
	}

	printf("\n");
}
