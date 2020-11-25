// NWERC 2015 - G - Guessing Camels
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

typedef long long ll;

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

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			upd(i, 1);
	}
} BIT;

int n;
int a[3][maxn];
int p[3][maxn];

int main(void)
{
	scanf("%d", &n);

	for (int j = 0; j < 3; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[j][i]);

			p[j][a[j][i]] = i;
		}
	}

	ll tot = 0;

	BIT.init(n);

	for (int i = 1; i <= n; i++)
	{
		int v = a[0][i], pos = p[1][v];

		tot += 1ll*BIT.soma(pos-1);

		BIT.upd(pos, -1);
	}

	memset(BIT.bit, 0, sizeof BIT.bit);
	BIT.init(n);

	for (int i = 1; i <= n; i++)
	{
		int v = a[0][i], pos = p[2][v];

		tot += 1ll*BIT.soma(pos-1);

		BIT.upd(pos, -1);
	}

	memset(BIT.bit, 0, sizeof BIT.bit);
	BIT.init(n);
	
	for (int i = 1; i <= n; i++)
	{
		int v = a[1][i], pos = p[2][v];

		tot += 1ll*BIT.soma(pos-1);

		BIT.upd(pos, -1);
	}

	assert(tot%2 == 0);
	tot /= 2;

	printf("%lld\n", 1ll*n*(n-1)/2ll - tot);
}
