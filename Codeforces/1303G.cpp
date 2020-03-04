// Codeforces 1303G - Sum of Prefix Sums
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef double dd;
typedef long long ll;
 
const int maxn = 2e5+10;

struct Line
{
	char type;
 
	dd x;
 
	ll m, b;
};

typedef set<Line>::iterator sit;

int a[maxn];

int sz[maxn];
bool mark[maxn];

ll SP[maxn], ans;

vector<int> grafo[maxn];

set<Line> env;
 
bool operator< (const Line &a, const Line &b)
{
	if (a.type + b.type > 0) return a.x < b.x;
 
	return a.m < b.m;
}
 
bool hasPrev(sit it)
{
	return (it != env.begin());
}

bool hasNext(sit it)
{
	return (next(it) != env.end());
}

dd intersect(Line l1, Line l2)
{
	return (dd)(l2.b-l1.b)/(l1.m-l2.m);
}

bool bad(Line l1, Line l2, Line l3)
{
	return intersect(l1, l3) < intersect(l1, l2);
}

void get_x(sit it)
{
	if (hasPrev(it))
	{
		Line l = *it;

		l.x = intersect(*prev(it), *it);

		env.erase(it); env.insert(l);
	}
}

void add(ll m, ll b)
{
	Line l = {0, 0, m, b};

	sit it = env.lower_bound(l);

	if (it != env.end() && it->m == l.m)
	{
		if (it->b >= l.b) return;
		env.erase(it);
	}

	env.insert(l);
	it = env.find(l);

	if (hasPrev(it) && hasNext(it) && bad(*prev(it), *it, *next(it)))
	{
		env.erase(it);
		return;
	}

	while (hasNext(it) && hasNext(next(it)) && bad(*it, *next(it), *next(next(it))))
		env.erase(next(it));

	while (hasPrev(it) && hasPrev(prev(it)) && bad(*prev(prev(it)), *prev(it), *it))
		env.erase(prev(it));

	if (hasNext(it)) get_x(next(it));
	get_x(it);
}

ll query(ll x)
{
	if (env.size() == 0) return 0;

	sit it = env.upper_bound({1, (dd)x, 0, 0});
	it--;

	return (it->m * x + it->b);
}

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v != p && !mark[v])
		{
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

int centroid(int u, int p, int S)
{
	for (auto v: grafo[u])
		if (v != p && !mark[v] && sz[v] > S/2)
			return centroid(v, u, S);

	return u;
}

void get_ans(int u, int p, int d, ll soma, int v_root)
{
	SP[u] = SP[p] + 1ll*d*a[u];
	ans = max({ans, SP[u], SP[u] + query(soma) - 1ll*v_root});

	for (auto v: grafo[u])
		if (v != p && !mark[v])
			get_ans(v, u, d+1, soma+1ll*a[v], v_root);
}

void upd(int u, int p, int d, ll soma)
{
	SP[u] = SP[p]+soma;
	ans = max(ans, SP[u]);
	add(d, SP[u]);

	for (auto v: grafo[u])
		if (v != p && !mark[v])
			upd(v, u, d+1, soma+1ll*a[v]);
}

void decompose(int u)
{
	dfs(u, 0);

	int c = centroid(u, 0, sz[u]);
	mark[c] = 1;

	SP[c] = a[c];
	ans = max(ans, SP[c]);

	for (auto v: grafo[c])
	{
		if (mark[v]) continue;

		get_ans(v, c, 2, a[v], a[c]);
		upd(v, c, 1, a[c]+a[v]);
	}

	env.clear();

	for (int i = grafo[c].size()-1; i >= 0; i--)
	{
		int v = grafo[c][i];
		if (mark[v]) continue;

		get_ans(v, c, 2, a[v], a[c]);
		upd(v, c ,1, a[c]+a[v]);
	}

	env.clear();

	for (auto v: grafo[c])
		if (!mark[v])
			decompose(v);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	decompose(1);

	printf("%lld\n", ans);
}
