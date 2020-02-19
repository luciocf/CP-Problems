// Codeforces 840D - Destiny
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

struct Query
{
	int l, r, k, bloco, id;
} query[maxn];

int n;
int a[maxn];

int ans[maxn];

int fq[maxn];

bool comp(Query a, Query b)
{
	if (a.bloco == b.bloco) return a.r < b.r;
	return a.bloco < b.bloco;
}

int main(void)
{
	mt19937 mt;

	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int sq = sqrt(n)+1;

	for (int i = 1; i <= m; i++)
	{
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);

		query[i] = {l, r, k, l/sq, i};
	}

	sort(query+1, query+m+1, comp);

	int l = 1, r = 1;
	fq[a[1]]++;

	for (int i = 1; i <= m; i++)
	{
		int ql = query[i].l, qr = query[i].r;

		while (r > qr) fq[a[r--]]--;
		while (r < qr) fq[a[++r]]++;
		while (l > ql) fq[a[--l]]++;
		while (l < ql) fq[a[l++]]--;

		int num = 1e9+10;
		uniform_int_distribution<int> rng(l, r);

		for (int it = 1; it <= 300; it++)
		{
			int x = a[rng(mt)];

			if (fq[x] > (r-l+1)/query[i].k)
				num = min(num, x);
		}

		if (num == 1e9+10) ans[query[i].id] = -1;
		else ans[query[i].id] = num;
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
