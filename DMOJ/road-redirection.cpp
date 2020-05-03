// DMOJ - Road Redirection
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int st[maxn], en[maxn], tt;
int nivel[maxn];

int bit[maxn];

pii edge[maxn];

vector<int> grafo[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

void upd(int l, int r, int v)
{
	upd(l, v); upd(r+1, -v);
}

void dfs(int u, int p)
{
	st[u] = ++tt;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		dfs(v, u);
	}

	en[u] = tt;
}

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);

		edge[i] = {u, v};
	}

	dfs(1, 0);

	for (int i = 1; i < n; i++)
	{
		int u = edge[i].first, v = edge[i].second;

		if (nivel[u] > nivel[v])
		{
			upd(1, n, 1);
			upd(st[u], en[u], -1);
		}
		else
		{
			upd(st[v], en[v], 1);
		}
	}

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int u;
			scanf("%d", &u);

			printf("%d\n", soma(st[u]));
		}
		else
		{
			int r;
			scanf("%d", &r);

			swap(edge[r].first, edge[r].second);
			int u = edge[r].first, v = edge[r].second;

			if (nivel[u] > nivel[v])
			{
				upd(1, n, 1);
				upd(st[u], en[u], -2);
			}
			else
			{
				upd(1, n, -1);
				upd(st[v], en[v], 2);
			}
		}
	}
}
