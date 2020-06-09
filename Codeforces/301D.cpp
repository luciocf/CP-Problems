// Codeforces 301D - Yaroslav and Divisors
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

struct Query
{
	int l, r, ind;
} query[maxn];

int a[maxn];
int pos[maxn];

int bit[maxn];

int ans[maxn];

vector<int> d[maxn];

bool comp(Query a, Query b) {return a.r < b.r;}

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		pos[a[i]] = i;
	}

	for (int i = 1; i <= n; i++)
		for (int j = a[i]; j <= n; j += a[i])
			if (pos[j] >= i)
				d[pos[j]].push_back(i);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &query[i].l, &query[i].r);
		query[i].ind = i;
	}

	sort(query+1, query+m+1, comp);

	int ptr = 1;
	for (int i = 1; i <= m; i++)
	{
		int l = query[i].l, r = query[i].r;

		while (ptr <= r)
		{
			for (auto pos: d[ptr])
				upd(pos, 1);

			for (int j = a[ptr]; j <= n; j += a[ptr])
				if (pos[j] < ptr)
					upd(pos[j], 1);

			++ptr;
		}

		ans[query[i].ind] = soma(r)-soma(l-1);
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
