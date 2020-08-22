// Codeforces 1389F - Bicolored Segments
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 4e5+10;

pii range[maxn];
bool mark[maxn];

struct Event
{
	int x, c, t, ind;
} event[maxn];

bool comp(Event a, Event b)
{
	if (a.x == b.x) return a.t < b.t;
	return a.x < b.x;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int aux = 0;

	for (int i = 1; i <= n; i++)
	{
		int l, r, c;
		scanf("%d %d %d", &l, &r, &c);
		--c;

		range[i] = {l, r};

		event[++aux] = {l, c, 0, i};
		event[++aux] = {r, c, 1, i};
	}

	sort(event+1, event+aux+1, comp);

	multiset<pii> st[2];

	int match = 0;

	for (int i = 1; i <= aux; i++)
	{
		auto e = event[i];

		if (e.t == 0) st[e.c].insert({range[e.ind].ss, e.ind});
		else
		{
			if (st[!e.c].size() && !mark[e.ind])
			{
				++match;

				mark[e.ind] = mark[st[!e.c].begin()->ss] = 1;

				st[!e.c].erase(st[!e.c].begin());
				st[e.c].erase(st[e.c].find({range[e.ind].ss, e.ind}));
			}
			
			if (!mark[e.ind]) st[e.c].erase(st[e.c].find({range[e.ind].ss, e.ind}));
		}
	}

	printf("%d\n", n-match);
}
