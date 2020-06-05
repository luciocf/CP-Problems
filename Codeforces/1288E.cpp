// Codeforces 1288E - Messenger Simulator
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;
const int sq = 400;

struct Query
{
	int bucket, l, r, id;
} query[maxn];

int n, m;
int a[maxn];

bool mark[maxn];

int ans[maxn];

int fq[maxn], tot = 1;

int bit[maxn];

vector<int> pos[maxn];

bool comp(Query a, Query b)
{
	if (a.bucket == b.bucket) return a.r < b.r;
	return a.bucket < b.bucket;
}

bool comp2(int a, int b)
{
	return pos[a][0] < pos[b][0];
}

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

void add(int i)
{
	if (fq[a[i]] == 0) ++tot;
	++fq[a[i]];
}

void rem(int i)
{
	if (fq[a[i]] == 1) --tot;
	--fq[a[i]];
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int p;
		scanf("%d", &p);

		a[i] = p;
		pos[p].push_back(i);

		mark[p] = 1;
	}

	int antes = 0, q = 0;
	for (int i = n; i >= 1; i--)
	{
		if (!mark[i]) ans[i] = i+antes;
		else
		{
			++antes;

			for (int j = 1; j < pos[i].size(); j++)
			{
				int l = pos[i][j-1], r = pos[i][j]-1;
				int b = l/sq;

				query[++q] = {b, l, r, i};
			}

			if (pos[i].back() != m)
			{
				int l = pos[i].back(), r = m;
				int b = l/sq;

				query[++q] = {b, l, r, i};
			}

		}
	}

	sort(query+1, query+q+1, comp);

	int l = 1, r = 1;
	fq[a[1]]++;

	for (int i = 1; i <= q; i++)
	{
		while (l > query[i].l) add(--l);
		while (l < query[i].l) rem(l++);
		while (r > query[i].r) rem(r--);
		while (r < query[i].r) add(++r);

		ans[query[i].id] = max(ans[query[i].id], tot);
	}

	vector<int> perm;

	for (int i = 1; i <= n; i++)
		if (mark[i])
			perm.push_back(i);

	sort(perm.begin(), perm.end(), comp2);

	for (auto p: perm)
	{
		ans[p] = max(ans[p], p+(soma(n)-soma(p)));
		upd(p, 1);
	}

	for (int i = 1; i <= n; i++)
	{
		if (!mark[i]) printf("%d %d\n", i, ans[i]);
		else printf("1 %d\n", max(i, ans[i]));
	}
}
