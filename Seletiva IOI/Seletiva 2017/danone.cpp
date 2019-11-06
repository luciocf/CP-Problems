// Seletiva IOI 2017 - Danone
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e6+10;

struct Q
{
	char op;
	int l, r;
} q[maxn];

int n, m;
int a[maxn];

int pai[maxn], peso[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

void dfs(int u)
{
	mark[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;

		if (mark[v]) continue;

		if (v > u) a[v] = a[u]+w;
		else a[v] = a[u]-w;

		dfs(v);
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		char op;
		scanf(" %c", &op);

		if (op == 'L')
		{
			int l, r, v;
			scanf("%d %d %d", &l, &r, &v);

			grafo[r].push_back({l-1, v});
			grafo[l-1].push_back({r, v});

			q[i] = {op, l-1, r};
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			q[i] = {op, l-1, r};
		}
	}

	init();

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);

	for (int i = 1; i <= m; i++)
	{
		if (q[i].op == 'L') Join(q[i].l, q[i].r);
		else
		{
			if (Find(q[i].l) != Find(q[i].r)) printf("Esquecido\n");
			else printf("%d\n", a[q[i].r]-a[q[i].l]);
		}
	}
}
