// Codeforces 594D - REQ
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;
const int mod = 1e9+7;

struct Query
{
	int l, r, id;
} qry[maxn];

int n;
int a[maxn];

int spf[maxn];

int bit[maxn];

int last[maxn];

int ans[maxn];

bool comp(Query a, Query b) {return a.r < b.r;}

void sieve(void)
{
	for (int i = 1; i < maxn; i++)
		spf[i] = i;

	for (int i = 2; i*i < maxn; i++)
		if (spf[i] == i)
			for (int j = 2*i; j < maxn; j += i)
				if (spf[j] == j)
					spf[j] = i;
}

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b%2) return (1ll*a*((1ll*t*t)%mod))%mod;

	return (1ll*t*t)%mod;
}

int inverse(int a)
{
	return pot(a, mod-2);
}

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] = (1ll*bit[x]*v)%mod;
}

int prod(int x)
{
	int ans = 1;

	for (; x > 0; x -= (x&-x))
		ans = (1ll*ans*bit[x])%mod;

	return ans;
}

int main(void)
{
	sieve();
	for (int i = 1; i < maxn; i++)
		bit[i] = 1;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		upd(i, a[i]);
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d", &qry[i].l, &qry[i].r);
		qry[i].id = i;
	}

	sort(qry+1, qry+q+1, comp);

	int ind = 1;
	for (int i = 1; i <= n; i++)
	{
		int x = a[i];

		while (x > 1)
		{
			int p = spf[x];

			if (last[p] < i)
			{
				if (last[p])
				{
					upd(last[p], inverse(p-1));
					upd(last[p], p);
				}

				upd(i, p-1);
				upd(i, inverse(p));
			}

			x /= p;
			last[p] = i;
		}

		while (qry[ind].r == i)
		{
			int a = prod(i);
			int b = inverse(prod(qry[ind].l-1));

			ans[qry[ind].id] = (1ll*a*b)%mod;
			++ind;
		}
	}

	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
