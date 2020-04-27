// Codeforces 932F - Escape Through Leaf
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef double dd;
typedef long long ll;

struct Line
{
	char type;

	dd x;

	ll m, b;
};

int vez;

typedef set<Line>::iterator sit;

int n;
int A[maxn], B[maxn];

ll dp[maxn];

vector<int> grafo[maxn];

set<Line> env[maxn];

bool operator< (const Line &a, const Line &b)
{
	if (a.type + b.type > 0) return a.x < b.x;

	return a.m > b.m;
}

bool hasPrev(sit it, int id)
{
	return (it != env[id].begin());
}

bool hasNext(sit it, int id)
{
	return (it != env[id].end() && (++it) != env[id].end());
}

dd intersect(Line l1, Line l2)
{
	return (dd)(l2.b-l1.b)/(dd)(l1.m-l2.m);
}

bool bad(Line l1, Line l2, Line l3)
{
	return intersect(l1, l3) < intersect(l1, l2);
}

void get_x(sit it, int id)
{
	if (hasPrev(it, id))
	{
		Line l = *it;

		l.x = intersect(*prev(it), *it);
		
		env[id].erase(it);
		env[id].insert(l);
	}
}

void add(ll m, ll b, int id)
{
	Line l = {0, -maxn, m, b};

	sit it = env[id].lower_bound(l);

	if (it != env[id].end() && it->m == m)
	{
		if (it->b <= b) return;
		env[id].erase(it);
	}
    
	env[id].insert(l);
	it = env[id].find(l);
    
	if (hasPrev(it, id) && hasNext(it, id) && bad(*prev(it), *it, *next(it)))
	{
		env[id].erase(it);
		return;
	}

	while (hasPrev(it, id) && hasPrev(prev(it), id) && bad(*prev(prev(it)), *prev(it), *it))
		env[id].erase(prev(it));

	while (hasNext(it, id) && hasNext(next(it), id) && bad(*it, *next(it), *next(next(it))))
		env[id].erase(next(it));
    
    if (hasNext(it, id)) get_x(next(it), id);
	get_x(it, id);
}

ll query(ll x, int id)
{
	sit it = env[id].upper_bound({1, (dd)x, 0, 0});
	it--;

	return (it->m*x + it->b);
}

void solve(int u, int p)
{
    for (auto v: grafo[u])
    {
		if (v == p) continue;
		solve(v, u);
		
		if (env[v].size() > env[u].size()) swap(env[u], env[v]);
        
		for (auto l: env[v])
		    add(l.m, l.b, u);
    }
    
	if ((int)grafo[u].size() == 1 && u != 1) dp[u] = 0;
	else dp[u] = query(A[u], u);

	add(B[u], dp[u], u);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &A[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &B[i]);

	if (n == 1)
	{
		printf("0\n");
		return 0;
	}

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	solve(1, 0);

	for (int i = 1; i <= n; i++)
		printf("%lld ", dp[i]);
	printf("\n");
}
