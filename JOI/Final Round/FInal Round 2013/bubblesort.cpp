// JOI Final Round 2013 - Bubble Sort
// Lúcio Cardoso

#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n;

struct Node
{
	Node *l, *r;
	int v;

	Node()
	{
		l = r = NULL;
		v = 0;
	}
};

Node *version[maxn];

struct PersistentSegmentTree
{
	int val(Node *node)
	{
		return (node ? node->v : 0);
	}

	void build(Node *node, int l, int r)
	{
		if (l == r) return;

		int mid = (l+r)>>1;

		node->l = new Node(); node->r = new Node();

		build(node->l, l, mid); build(node->r, mid+1, r);
	}

	void upd(Node *node, Node *prev, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			node->v = prev->v + v;
			return;
		}

		int mid = (l+r)>>1;

		if (pos <= mid)
		{
			if (!node->l) node->l = new Node();
			node->r = prev->r;

			upd(node->l, prev->l, l, mid, pos, v);
		}
		else
		{
			if (!node->r) node->r = new Node();
			node->l = prev->l;

			upd(node->r, prev->r, mid+1, r, pos, v);
		}

		node->v = val(node->l) + val(node->r);
	}

	int query(Node *node, Node *prev, int l, int r, int a, int b)
	{
		if (!node || l > b || r < a) return 0;
		if (l >= a && r <= b) return node->v - prev->v;

		int mid = (l+r)>>1;

		return query(node->l, prev->l, l, mid, a, b) + query(node->r, prev->r, mid+1, r, a, b);
	}

	int get(int l, int r, int a, int b)
	{
		if (l > r || a > b) return 0;

		return query(version[r], version[l-1], 1, n, a, b);
	}
} seg;

int a[maxn];

ll tot_inv, ans;

int opt[maxn];
vector<int> candidates;

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]];
}

void solve(int l, int r)
{
	if (l > r) return;

	int mid = (l+r)>>1;

	int l_opt = (l == 0 ? 1 : opt[l-1]);
	int r_opt = (r == candidates.size()-1 ? n : opt[r+1]);
	int pos = candidates[mid];

	ll val = tot_inv;

	for (int i = max(l_opt, pos+1); i <= r_opt; i++)
	{
		if (a[i] >= a[pos]) continue;

		int at = seg.get(pos+1, i-1, a[i]+1, a[pos]-1) + seg.get(pos, i, a[i], a[pos]) - 1;

		if (tot_inv - 1ll*at < val)
		{
			val = tot_inv - 1ll*at;
			opt[mid] = i;
		}
	}

	ans = min(ans, val);

	solve(l, mid-1); solve(mid+1, r);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	compress();

	version[0] = new Node();

	seg.build(version[0], 1, n);

	for (int i = 1; i <= n; i++)
	{
		version[i] = new Node();

		seg.upd(version[i], version[i-1], 1, n, a[i], 1);
	}

	for (int i = 2; i <= n; i++)
		tot_inv += 1ll*seg.get(1, i-1, a[i]+1, n);

	if (tot_inv == 0)
	{
		bool ok = 0;
		for (int i = 2; i <= n; i++)
			if (a[i] == a[i-1])
				ok = 1;

		if (ok) printf("0\n");
		else printf("1\n");
		return 0;
	}

	int mn = 1e9+10;

	for (int i = n; i >= 1; i--)
	{
		if (a[i] <= mn)
		{
			mn = min(mn, a[i]);
			continue;
		}

		while (candidates.size() && a[i] >= a[candidates.back()])
			candidates.pop_back();

		candidates.push_back(i);

		mn = min(mn, a[i]);
	}

	reverse(candidates.begin(), candidates.end());

	ans = tot_inv;
	solve(0, candidates.size()-1);

	printf("%lld\n", ans);
}
