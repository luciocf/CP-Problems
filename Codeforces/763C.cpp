// Codeforces 763C - Timofey and remoduling
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 1e5+10;

int n, mod;
int a[maxn], b[maxn];

map<int, int> tem;

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
	return (1ll*t*t)%mod;
}

int inv(int x)
{
	return pot(x, mod-2);
}

pair<int, int> get(int pos)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
	{
		if (i == pos) continue;

		int dif = (a[pos]-a[i]+mod)%mod;
		mp[dif] = i;
	}

	int tot = 0;

	for (int i = 1; i <= n; i++)
	{
		if (i == pos) continue;

		int dif = (a[pos]-a[i]+mod)%mod;

		if (mp[(mod-dif)%mod])
			++tot;
	}

	tot /= 2;


	return {tot+1, n-tot};
}

int get_d(int pos1, int pos2)
{
	pos1--, pos2--;

	int k = (a[1] - a[2] + mod)%mod;
	return (1ll*k*inv((pos1-pos2+mod)%mod))%mod;
}

int get_x(int d, int pos1)
{
	pos1--;
	int x = (a[1] - ((1ll*d*pos1)%mod) + mod)%mod;

	for (int i = 1; i <= n; i++)
		tem[a[i]] = 0;
	for (int i = 1; i <= n; i++)
		tem[a[i]]++;

	for (int i = 0; i < n; i++)
	{
		int val = (1ll*x + 1ll*i*d)%mod;

		if (!tem[val])
			return -1;

		tem[val]--;
	}

	return x;
}

int main(void)
{
	scanf("%d %d", &mod, &n);

	int n_0 = n;

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	if (mod == n)
	{
		printf("1 1\n");
		return 0;
	}

	if (mod == n+1)
	{
		map<int, int> is;
		for (int i = 1; i <= n; i++)
			is[a[i]] = 1;

		int k;
		for (int i = 0; i < mod; i++)
			if (!is[i])
				k = i;

		printf("%d 1\n", k+1);
		return 0;
	}

	bool flag = 0;
	if (2*n > mod)
	{
		map<int, int> is;

		for (int i = 1; i <= n; i++)
			is[a[i]] = 1;

		int aux = 0;

		for (int i = 0; i < mod; i++)
			if (!is[i])
				b[++aux] = i;

		swap(a, b);
		swap(n, aux);
		flag = 1;
	}

	pair<int, int> pos_1 = get(1);
	pair<int, int> pos_2 = get(2);

	int d = get_d(pos_1.ff, pos_2.ff), x = get_x(d, pos_1.ff);

	if (x != -1)
	{
		if (!flag) printf("%d %d\n", x, d);
		else printf("%lld %d\n", (1ll*x + (1ll*(mod-n_0)*d))%mod, d);
		return 0;
	}

	d = get_d(pos_1.ff, pos_2.ss), x = get_x(d, pos_1.ff);

	if (x != -1)
	{
		if (!flag) printf("%d %d\n", x, d);
		else printf("%lld %d\n", (1ll*x + (1ll*(mod-n_0)*d))%mod, d);
		return 0;
	}

	d = get_d(pos_1.ss, pos_2.ff), x = get_x(d, pos_1.ss);

	if (x != -1)
	{
		if (!flag) printf("%d %d\n", x, d);
		else printf("%lld %d\n", (1ll*x + (1ll*(mod-n_0)*d))%mod, d);
		return 0;
	}

	d = get_d(pos_1.ss, pos_2.ss), x = get_x(d, pos_1.ss);

	if (x != -1)
	{
		if (!flag) printf("%d %d\n", x, d);
		else printf("%lld %d\n", (1ll*x + (1ll*(mod-n_0)*d))%mod, d);
		return 0;
	}

	printf("-1\n");
}
