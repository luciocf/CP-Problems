// Seletiva IOI 2018 - Amigo Secreto
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n;
int f[maxn], c[maxn];

int pai[maxn], peso[maxn];

int head[maxn], nivel[maxn];
bool mark[maxn];

vector<int> go[maxn];

multiset<int> st[maxn];

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

	if (mark[f[u]] && nivel[f[u]] == -1)
	{
		head[Find(u)] = u, nivel[u] = 0;
		return;
	}

	if (!mark[f[u]]) dfs(f[u]);

	nivel[u] = nivel[f[u]]+1;
}

void pre(void)
{
	for (int i = 1; i <= n; i++)
		if (!mark[i])
			dfs(i);
}

ll solve(int cc)
{
	for (int v = f[head[cc]]; ; v = f[v])
	{
		int u = f[v];

		if (st[u].find(-c[v]) != st[u].end())
			return 0;

		if (v == head[cc]) break;
	}

	int mn = 2e9+10;

	for (int v = f[head[cc]]; ; v = f[v])
	{
		int u = f[v];

		if (st[u].size() == 0) mn = min(mn, c[v]);
		else mn = min(mn, c[v]+(*st[u].begin()));

		if (v == head[cc]) break;
	}

	return 1ll*mn;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &f[i], &c[i]);

		go[f[i]].push_back(c[i]);
	}

	if (n == 1)
	{
		printf("0\n");
		return 0;
	}

	for (int i = 1; i <= n; i++)
		for (auto v: go[i])
			st[i].insert(-v);

	for (int i = 1; i <= n; i++)
		if (st[i].size())
			st[i].erase(st[i].begin());

	ll ans = 0;
	for (int i = 1; i <= n; i++)
		for (auto x: st[i])
			ans += 1ll*(-x);

	init();

	for (int i = 1; i <= n; i++)
		if (Find(i) != Find(f[i]))
			Join(i, f[i]);

	memset(nivel, -1, sizeof nivel);
	pre();

	for (int i = 1; i <= n; i++)
		if (i == Find(i))
			ans += solve(Find(i));

	bool ok = 1;
	for (int i = 1; i <= n; i++)
		if (Find(i) != Find(1))
			ok = 0;

	if (ok && nivel[f[head[Find(1)]]] == n-1)
	{
		printf("0\n");
		return 0;
	}

	printf("%lld\n", ans);
}
