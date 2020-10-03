// 2015-2016 6th BSUIR Open Programming Contest Semifinal - A - LIS and GCD
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxv = 1e6+10;
const int mod = 1e9+7;

struct FenwickTree
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] = (bit[x] + v)%mod;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans = (ans + bit[x])%mod;
		return ans;
	}

	int get(int l, int r)
	{
		if (l > r) return 0;
		return (soma(r) - soma(l-1) + mod)%mod;
	}
} BIT;

int n;
pii a[maxn];

int tot[maxv];

vector<int> ind[maxv];

void compress(void)
{
	map<int, int> mp;
	for (int i = 1; i <= n; i++)
		mp[a[i].ff] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i].ff = mp[a[i].ff];
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i].ff);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i].ss);

	compress();

	for (int i = 1; i <= n; i++)
	{
		int v = a[i].ss;

		for (int j = 1; j*j <= v; j++)
		{
			if (v%j) continue;

			ind[j].push_back(i);

			if (j != v/j) ind[v/j].push_back(i);
		}
	}

	for (int v = 1; v < maxv; v++)
	{	
		for (auto i: ind[v])
		{
			tot[v] = (tot[v] + BIT.get(1, a[i].ff-1) + 1)%mod;

			BIT.upd(a[i].ff, BIT.get(1, a[i].ff-1) + 1);
		}

		for (auto i: ind[v])
			BIT.upd(a[i].ff, (mod-BIT.get(a[i].ff, a[i].ff)%mod));
	}

	int ans = 0;

	for (int i = maxv-1; i >= 1; i--)
	{
		for (int j = 2*i; j < maxv; j += i)
			tot[i] = (tot[i] - tot[j] + mod)%mod;

		ans = (ans + (1ll*i*tot[i])%mod)%mod;
	}

	printf("%d\n", ans);
}
