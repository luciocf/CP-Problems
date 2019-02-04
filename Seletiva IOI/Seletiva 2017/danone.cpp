// Seletiva IOI 2017 - Danone
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6+10;

typedef pair<int, int> pii;

struct Q
{
	int op, l, r;
} query[maxn];

int num[maxn];

int pai[maxn], sz[maxn];

bool mark[maxn];

vector<pii> grafo[maxn];

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (sz[x] < sz[y]) swap(x, y);

	pai[y] = x, sz[x] += sz[y];
}

void init(int n)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, sz[i] = 1;
}

void dfs(int u)
{
	mark[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.first, x = pp.second;
		if (mark[v]) continue;

		if (v < u) num[v] = num[u]-x;
		else num[v] = num[u]+x;

		dfs(v);
	}
}

int main(void)
{
	int n, q;
	cin >> n >> q;

	init(n);

	for (int i = 1; i <= q; i++)
	{
		char op;
		cin >> op;

		if (op == 'C')
		{
			int l, r;
			cin >> l >> r;

			query[i] = {0, l, r};
		}
		else
		{
			int l, r, x;
			cin >> l >> r >> x;

			grafo[l-1].push_back({r, x});
			grafo[r].push_back({l-1, x});

			query[i] = {1, l, r};
		}
	}

	for (int i = 0; i <= n; i++)
		if (!mark[i])
			dfs(i);

	for (int i = 1; i <= q; i++)
	{
		int l = query[i].l, r = query[i].r;

		if (query[i].op) Join(l-1, r);
		else
		{
			if (Find(l-1) != Find(r)) cout << "Esquecido\n";
			else cout << num[r]-num[l-1] << "\n";
		}
	}
}