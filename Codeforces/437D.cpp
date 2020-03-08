// Codeforces 437D - The Child and Zoo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;

pii a[maxn];

int pai[maxn], peso[maxn];

bool mark[maxn], aux[maxn];

vector<int> grafo[maxn];

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
	int n, m;
	scanf("%d %d", &n, &m);

	init(n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].first);
		a[i].second = i;
	}

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	ll ans = 0;

	sort(a+1, a+n+1);

	for (int i = n; i >= 1; i--)
	{
		int u = a[i].second;
		mark[u] = 1;

		int tot = 1;

		for (auto v: grafo[u])
		{
			if (mark[v] && !aux[Find(v)])
			{
				tot += peso[Find(v)];
				aux[Find(v)] = 1;
			}
		}

		for (auto v: grafo[u])
			aux[Find(v)] = 0;

		ans += 1ll*a[i].first*(tot-1);
		for (auto v: grafo[u])
		{
			if (mark[v] && !aux[Find(v)])
			{
				ans += 1ll*a[i].first*peso[Find(v)]*(tot-peso[Find(v)]);
				aux[Find(v)] = 1;
			}
		}

		for (auto v: grafo[u])
		{
			aux[Find(v)] = 0;
			if (mark[v]) Join(u, v);
		}
	}

	double anss = ans;
	double baixo = (double)n*(n-1);

	printf("%.9lf\n", anss/baixo);
}
