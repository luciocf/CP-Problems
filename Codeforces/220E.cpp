// Codeforces 220E - Little Elephant and Inversions
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

struct BIT
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
} b_pref, b_suf;

int n;
ll k;

int a[maxn];

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]];
}

int main(void)
{
	scanf("%d %lld", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	compress();

	ll inv = 0;

	for (int i = n; i >= 2; i--)
	{
		inv += 1ll*b_suf.soma(a[i]-1);
		b_suf.upd(a[i], 1);
	}

	ll ans = 0;
	int l = 1, r = 2;

	for (; l <= n; l++)
	{
		inv += 1ll*(b_pref.soma(n)-b_pref.soma(a[l]));
		b_pref.upd(a[l], 1);
		inv += 1ll*b_suf.soma(a[l]-1);

		while ((inv > k || r <= l) && r <= n)
		{
			inv -= 1ll*b_suf.soma(a[r]-1);
			inv -= 1ll*(b_pref.soma(n)-b_pref.soma(a[r]));
			b_suf.upd(a[r], -1);

			++r;
		}

		if (r <= n) ans += 1ll*(n-r+1);
	}

	printf("%lld\n", ans);
}
