// Codeforces 979D - Kuro and GCD and XOR and SUM
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9;

struct node
{
	int mn;
	node *b[2];

	node()
	{
		mn = inf;
		b[0] = b[1] = NULL;
	}
};

node *root[maxn];

vector<int> D[maxn];

bool mark[maxn];

void add(node *t, int v)
{
	node *at = t;

	for (int i = 20; i >= 0; i--)
	{
		at->mn = min(at->mn, v);

		int c = ((v&(1<<i)) ? 1 : 0);

		if (!at->b[c]) at->b[c] = new node();

		at = at->b[c];
	}

	at->mn = min(at->mn, v);
}

int query(node *t, int x, int s)
{
	node *at = t;
	int ans = 0;

	for (int i = 20; i >= 0; i--)
	{
		if (!at || at->mn > s-x) return -1;

		if (x&(1<<i))
		{
			if (at->b[0] && at->b[0]->mn <= s-x)
				at = at->b[0];
			else
			{
				ans += (1<<i);
				at = at->b[1];
			}
		}
		else
		{
			if (at->b[1] && at->b[1]->mn <= s-x)
			{
				ans += (1<<i);
				at = at->b[1];
			}
			else at = at->b[0];
		}
	}

	if (at->mn > s-x) return -1;
	return ans;
}

int main(void)
{
	int q;
	scanf("%d", &q);

	for (int i = 1; i < maxn; i++)
	{
		root[i] = new node();

		for (int j = i; j < maxn; j += i)
			D[j].push_back(i);
	}

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int u;
			scanf("%d", &u);

			if (mark[u]) continue;

			mark[u] = 1;
			for (auto d: D[u])
				add(root[d], u);
		}
		else
		{
			int x, k, s;
			scanf("%d %d %d", &x, &k, &s);

			if (x%k)
			{
				printf("-1\n");
				continue;
			}

			printf("%d\n", query(root[k], x, s));
		}
	}
}
