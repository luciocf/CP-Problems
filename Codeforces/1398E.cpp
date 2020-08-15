// Codeforces 1398E - Two Types of Spells
// Lúcio Cardoso

// Solution is the same as in editorial, using a dynamic segment tree

#include <bits/stdc++.h>

using namespace std;

const int maxv = 1e9+10;

typedef long long ll;

struct Node
{
	Node *l, *r;
	ll v;
	int qtd;

	Node() {l = r = NULL; v = qtd = 0;}
};

Node *root;

struct SegmentTree
{
	ll getv(Node *node)
	{
		return (node ? node->v : 0);
	}

	ll getqtd(Node *node)
	{
		return (node ? node->qtd : 0);
	}

	void upd(Node *node, int l, int r, int pos, int v, int add)
	{
		if (l == r)
		{ 
			node->v += 1ll*v;
			node->qtd += add;

			return;
		}

		int mid = (l+r)>>1;

		if (pos <= mid)
		{
			if (!node->l) node->l = new Node();
			upd(node->l, l, mid, pos, v, add);
		}
		else
		{
			if (!node->r) node->r = new Node();
			upd(node->r, mid+1, r, pos, v, add);
		}

		node->v = getv(node->l) + getv(node->r);
		node->qtd = getqtd(node->l) + getqtd(node->r);
	}

	ll query(Node *node, int l, int r, int k)
	{
		if (l == r) return 1ll*l*k;
		if (!node) return 0;

		int mid = (l+r)>>1;

		if (getqtd(node->r) >= k) return query(node->r, mid+1, r, k);
		return getv(node->r) + query(node->l, l, mid, k-getqtd(node->r));
	}
} seg;

int main(void)
{
	root = new Node();

	int q;
	scanf("%d", &q);

	multiset<int> st;
	ll soma = 0;

	while (q--)
	{
		int t, d;
		scanf("%d %d", &t, &d);

		soma += 1ll*d;

		if (d > 0)
		{
			if (t == 0) seg.upd(root, 1, maxv-1, d, d, 1);
			else
			{
				if (st.size() && d >= *st.begin())
					seg.upd(root, 1, maxv-1, d, d, 1);
				else if (st.size() && d < *st.begin())
					seg.upd(root, 1, maxv-1, *st.begin(), *st.begin(), 1);

				st.insert(d);
			}
		}
		else
		{
			d = abs(d);

			if (t == 0) seg.upd(root, 1, maxv-1, d, -d, -1);
			else
			{
				if (st.size() && d != *st.begin()) seg.upd(root, 1, maxv-1, d, -d, -1);

				bool should = (d == *st.begin());

				st.erase(st.find(d));

				if (st.size() && should) seg.upd(root, 1, maxv-1, *st.begin(), -*st.begin(), -1);
			}
		}

		int k = min((ll)st.size(), seg.getqtd(root));

		printf("%lld\n", soma + seg.query(root, 1, maxv-1, k));
	}
}
