// Codeforces 1167F - Scalar Queries
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;
const int mod = 1e9+7;

int n;
int a[maxn];

struct FenwickTree
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] = (bit[x]+v)%mod;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans = (ans+bit[x])%mod;
		return ans;
	}

	int get(int l, int r)
	{
		if (l > r) return 0;
		return (soma(r)-soma(l-1)+mod)%mod;
	}
} BIT;

map<int, int> mp;

void compress(void)
{
	for (int i = 1; i <= n; i++)
		mp[a[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	compress();

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		BIT.upd(mp[a[i]], i);

		int x = (1ll*BIT.get(1, mp[a[i]])*(n-i+1))%mod;

		ans = (ans + ((1ll*a[i]*x)%mod))%mod;
	}


	for (int i = 1; i <= n; i++)
		BIT.upd(mp[a[i]], mod-i);

	for (int i = n; i >= 1; i--)
	{
		BIT.upd(mp[a[i]], n-i+1);

		int x = (1ll*BIT.get(1, mp[a[i]]-1)*i)%mod;

		ans = (ans + ((1ll*a[i]*x)%mod))%mod;
	}

	printf("%d\n", ans);
}
