// Codeforces 1045G - AI robots
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;
const int maxv = 1e9+10;

int n, k;

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

Node *tree[maxn];

struct SegmentTree
{
	int get(Node *node)
	{
		return (node ? node->v : 0);
	}

	void upd(Node *node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			node->v += v;
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

		node->v = get(node->l)+get(node->r);
	}

	int query(Node *node, int l, int r, int a, int b)
	{
		if (!node || l > b || r < a) return 0;
		if (l >= a && r <= b) return node->v;

		int mid = (l+r)>>1;

		return query(node->l, l, mid, a, b) + query(node->r, mid+1, r, a, b);
	}
} seg;

struct Robot
{
	int x, r, q;
} a[maxn];

struct Event
{
	int op, pos, ind;
} event[maxn];

map<int, int> mp;

void compress(void)
{
	for (int i = 1; i <= n; i++)
		mp[a[i].q] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;
}

bool comp(Event a, Event b)
{
	if (a.pos == b.pos) return a.op < b.op;
	return a.pos < b.pos;
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &a[i].x, &a[i].r, &a[i].q);

	compress();

	int aux = 0;
	for (int i = 1; i <= n; i++)
	{
		event[++aux] = {1, a[i].x-a[i].r, i};
		event[++aux] = {2, a[i].x, i};
		event[++aux] = {3, a[i].x+a[i].r, i};
	}

	sort(event+1, event+aux+1, comp);

	for (int i = 0; i < maxn; i++)
		tree[i] = new Node();

	ll ans = 0;

	for (int i = 1; i <= aux; i++)
	{
		auto e = event[i];

		if (e.op == 1)
		{
			int x = a[e.ind].x;
			int q = mp[a[e.ind].q];

			seg.upd(tree[q], 0, maxv, x, 1);
		}
		else if (e.op == 3)
		{
			int x = a[e.ind].x;
			int q = mp[a[e.ind].q];

			seg.upd(tree[q], 0, maxv, x, -1);
		}
		else
		{
			int x = a[e.ind].x, r = a[e.ind].r, q = a[e.ind].q;

			for (int y = max(0, q-k); y <= q+k; y++)
			{
				if (mp.find(y) == mp.end()) continue;

				ans += 1ll*seg.query(tree[mp[y]], 0, maxv, x-r, x-1);
			}
		}
	}

	sort(a+1, a+n+1, [&] (Robot a, Robot b) {return a.x < b.x;});

	for (int i = 1; i <= n; i++)
	{
		int j;
		for (j = i; j <= n && a[j].x == a[i].x; j++)
			;
		j--;

		vector<int> qi;
		qi.reserve(j-i+2);

		for (int l = i; l <= j; l++)
			qi.push_back(a[l].q);

		sort(qi.begin(), qi.end());

		int ptr = 0;
		for (int l = 0; l < qi.size(); l++)
		{
			while (ptr < qi.size() && qi[ptr]+k < qi[l])
				ptr++;

			if (ptr != qi.size()) ans += 1ll*(l-ptr);
		}

		i = j;
	}

	printf("%lld\n", ans);
}
