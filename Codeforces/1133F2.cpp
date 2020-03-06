// Codeforces 1133F2 - Spanning Tree with One Fixed Degree
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

int pai[maxn], peso[maxn];

pii edge[maxn];

bool mark[maxn];

map<pii, int> mp;

void init(int n)
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

int main(void)
{
	int n, m, D;
	scanf("%d %d %d", &n, &m, &D);

	init(n);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &edge[i].ff, &edge[i].ss);

		if (edge[i].ff != 1 && edge[i].ss != 1 && Find(edge[i].ff) != Find(edge[i].ss))
			Join(edge[i].ff, edge[i].ss);
	}

	vector<pii> ans;

	for (int i = 1; i <= m; i++)
	{
		if (edge[i].ff == 1 && !mark[Find(edge[i].ss)])
		{
			ans.push_back({1, edge[i].ss}), mark[Find(edge[i].ss)] = 1;
			mp[{1, edge[i].ss}] = 1, --D;
		}
		else if (edge[i].ss == 1 && !mark[Find(edge[i].ff)])
		{
			ans.push_back({1, edge[i].ff}), mark[Find(edge[i].ff)] = 1;
			mp[{1, edge[i].ff}] = 1, --D;
		}
	}

	if (D < 0)
	{
		printf("NO\n");
		return 0;
	}

	for (int i = 1; i <= m; i++)
	{
		if (edge[i].ff == 1 && !mp[{1, edge[i].ss}] && D > 0)
		{
			ans.push_back({1, edge[i].ss}), mark[Find(edge[i].ss)] = 1;
			--D;
		}
		else if (edge[i].ss == 1 && !mp[{1, edge[i].ff}] && D > 0)
		{
			ans.push_back({1, edge[i].ff}), mark[Find(edge[i].ff)] = 1;
			--D;
		}
	}

	if (D > 0)
	{
		printf("NO\n");
		return 0;
	}

	init(n);

	for (auto e: ans)
		Join(e.ff, e.ss);

	for (int i = 1; i <= m; i++)
	{
		if (edge[i].ff != 1 && edge[i].ss != 1 && Find(edge[i].ff) != Find(edge[i].ss))
		{
			Join(edge[i].ff, edge[i].ss);
			ans.push_back({edge[i].ff, edge[i].ss});
		}
	}

	printf("YES\n");
	for (auto e: ans)
		printf("%d %d\n", e.ff, e.ss);
}
