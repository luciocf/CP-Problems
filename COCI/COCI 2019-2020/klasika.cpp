// COCI 2019/2020 - Klasika
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

struct Q
{
	int op, u, v, vert;
} query[maxn];

struct Node
{
	Node *b[2];
	set<pii> S;

	Node()
	{
		b[0] = b[1] = NULL;
	}
};

int n=1;

int path[maxn];

int st[maxn], en[maxn], tt;

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
		if (v != p)
			dfs(v, u);
	
	en[u] = tt;
}

void add(Node *t, int u, int v)
{
	Node *at = t;

	for (int i = 30; i >= 0; i--)
	{
		if (v&(1<<i))
		{
			if (!at->b[1]) at->b[1] = new Node();
			at = at->b[1];
		}
		else
		{
			if (!at->b[0]) at->b[0] = new Node();
			at = at->b[0];
		}

		at->S.insert({st[u], en[u]});
	}

}

int get_max(Node *t, int u, int v)
{
	Node *at = t;
	int ans = 0;

	for (int i = 30; i >= 0; i--)
	{
		Node *l = at->b[0], *r = at->b[1];

		if (v&(1<<i))
		{
			if (l == NULL)
			{
				at = r;
				continue;
			}

			set<pii>::iterator it = l->S.lower_bound({st[u], 0});

			if (it == l->S.end())
			{
				at = r;
				continue;
			}

			if (it->second <= en[u])
			{
				ans += (1<<i);
				at = l;
			}
			else at = r;
		}
		else
		{
			if (r == NULL)
			{
				at = l;
				continue;
			}

			set<pii>::iterator it = r->S.lower_bound({st[u], 0});

			if (it == r->S.end())
			{
				at = l;
				continue;
			}

			if (it->second <= en[u])
			{
				ans += (1<<i);
				at = r;
			}
			else at = l;
		}
	}

	return ans;
}

int main(void)
{
	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		string s;
		cin >> s;

		int u, v;
		scanf("%d %d", &u, &v);

		if (s[0] == 'A')
		{
			grafo[u].push_back(++n);
			grafo[n].push_back(u);

			path[n] = path[u]^v;

			query[i] = {0, u, v, n};
		}
		else query[i] = {1, u, v, 0};
	}

	dfs(1, 0);

	Node *root = new Node();
	add(root, 1, 0);

	for (int i = 1; i <= q; i++)
	{
		int u = query[i].u, v = query[i].v;

		if (query[i].op == 1)
			printf("%d\n", get_max(root, v, path[u]));
		else
			add(root, query[i].vert, path[query[i].vert]);
	}
}
