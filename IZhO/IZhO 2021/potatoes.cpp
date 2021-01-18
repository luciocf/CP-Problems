// IZhO 2021 - Potatoes
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

struct Query
{
	int l, r;
	int ind;
} qry[maxn];

struct FenwickTree
{
	int bit[maxn];

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
} BIT;

int a[maxn];
ll tot[maxn];

int prim[maxn][18];

int ant[maxn][18], last[maxn][18];
vector<int> ind[maxn];

void add(int pos)
{
	int v = a[pos];

	for (int i = 0; i < 18; i++)
	{
		int md = pos%(1<<i);

		int lst = last[pos][i];

		if (lst && (prim[md][i] == 0 || prim[md][i] > lst))
		{
			if (prim[md][i] != 0) BIT.upd(prim[md][i], -1);

			prim[md][i] = lst;

			BIT.upd(prim[md][i], 1);				
		}
	}
}

int main(void)
{
	int n, x, y;
	scanf("%d %d %d", &n, &x, &y);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		ind[a[i]].push_back(i);
	}

	for (int i = 1; i <= n; i++)
	{
		reverse(ind[i].begin(), ind[i].end());

		for (auto pos: ind[i])
		{
			for (int j = 0; j < 18; j++)
			{
				int md = pos%(1<<j);

				last[pos][j] = ant[md][j];
				ant[md][j] = pos;
			}
		}

		for (auto pos: ind[i])
			for (int j = 0; j < 18; j++)
				ant[pos%(1<<j)][j] = 0;
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		qry[i] = {l, r, i};
	}

	sort(qry+1, qry+q+1, [&] (Query a, Query b) {return a.l > b.l;});

	int ptr = n;
	add(n);

	for (int i = 1; i <= q; i++)
	{
		int l = qry[i].l, r = qry[i].r, ind = qry[i].ind;

		while (ptr > l)
			add(--ptr);

		int toty = BIT.soma(r);

		tot[ind] = 1ll*y*toty + 1ll*x*(toty+1);
	}

	for (int i = 1; i <= q; i++)
		printf("%lld\n", tot[i]);
}
