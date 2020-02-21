// Codeforces 1278D - Segment Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e5+10;

struct Range
{
	int l, r, id;
} range[maxn];

int pai[maxn], peso[maxn];

set<pii> st;

bool comp(Range a, Range b)
{
	return a.r > b.r;
}

void Init(int n)
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

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

int main(void)
{
	int n;
	scanf("%d", &n);

	Init(n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &range[i].l, &range[i].r);

		range[i].id = i;
	}

	sort(range+1, range+n+1, comp);

	int edge = 0;

	for (int i = 1; i <= n; i++)
	{
		set<pii>::iterator it = st.upper_bound({range[i].l, 0});

		for (; it != st.end(); it++)
		{
			if (it->first > range[i].r) break;

			if (edge > n-1 || Find(range[i].id) == Find(it->second))
			{
				printf("NO\n");
				return 0;
			}

			Join(range[i].id, it->second);
			edge++;
		}

		st.insert({range[i].l, range[i].id});
	}

	if (edge == n-1) printf("YES\n");
	else printf("NO\n");
}
