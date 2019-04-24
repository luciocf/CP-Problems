// CEOI 2017 - Building Bridges
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

typedef double dd;

struct Line
{
	char type;

	dd x;

	ll m, b;
};

typedef set<Line>::iterator sit;

ll h[maxn], w[maxn];
ll dp[maxn];

set<Line> env;

bool operator< (const Line &a, const Line &b)
{
	if (a.type+b.type > 0) return a.x < b.x;

	return a.m > b.m;
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
		if (it->b <= l.b) return;
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

	get_x(it);
	if (hasNext(it)) get_x(next(it));
}

ll query(ll x)
{
	sit it = env.upper_bound({1, (dd)x, 0, 0});
	it--;

	return (it->m * x + it->b);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", &h[i]);

	ll S = 0;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &w[i]), S += 1ll*w[i];

	dp[1] = -w[1];

	add(-2*h[1], h[1]*h[1]-w[1]);

	for (int i = 2; i <= n; i++)
	{
		ll val = query(h[i]);

		dp[i] = h[i]*h[i] - w[i] + val;

		add(-2*h[i], h[i]*h[i]+dp[i]);
	}

	printf("%lld\n", S+dp[n]);
}
