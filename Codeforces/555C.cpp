#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9+10;

struct Node
{
	Node *l, *r;
	int v;

	Node()
	{
		v = inf;
		l = r = NULL;
	}
};

struct SegmentTree
{
	Node *tree;

	void init(void)
	{
		tree = new Node();
	}

	int get(Node *node)
	{
		return (node ? node->v : inf);
	}

	void upd(Node *node, int l, int r, int pos, int v)
	{
		if (l == r)
		{
			node->v = v;
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

		node->v = min(get(node->l), get(node->r));
	}

	int busca(Node *node, int l, int r, int a, int b, int v)
	{
		if (!node || l > b || r < a || node->v > v) return 0;
		if (l == r) return l;

		int mid = (l+r)>>1;

		int p1 = busca(node->r, mid+1, r, a, b, v);

		return (p1 ? p1 : busca(node->l, l, mid, a, b, v));
	}
} seg[2];

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	seg[0].init(); seg[1].init();

	map<int, int> mark[2];

	while (q--)
	{
		int x, y;
		char c;

		scanf("%d %d %c", &x, &y, &c);

		swap(x, y);

		if (c == 'L')
		{
			if (mark[0][x])
			{
				printf("0\n");
				continue;
			}

			mark[0][x] = 1;

			int ate = seg[1].busca(seg[1].tree, 1, n, 1, y, x);

			printf("%d\n", y-ate);

			seg[0].upd(seg[0].tree, 1, n, x, ate+1);
		}
		else
		{
			if (mark[1][y])
			{
				printf("0\n");
				continue;
			}

			mark[1][y] = 1;
			
			int ate = seg[0].busca(seg[0].tree, 1, n, 1, x, y);

			if (ate == x)
			{
				printf("0\n");
				continue;
			}

			printf("%d\n", x-ate);

			seg[1].upd(seg[1].tree, 1, n, y, ate+1);
		}
	}
}
