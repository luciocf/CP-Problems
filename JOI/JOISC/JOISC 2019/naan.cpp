// JOISC 2019 - Naan
// Lúcio Cardoso

// Solution is the same as in: https://github.com/thecodingwizard/competitive-programming/blob/master/JOI/JOISC%2019-Naan.cpp

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 2e3+10;

int a[maxn][maxn];
ll soma[maxn];

pii split[maxn][maxn];

bool mark[maxn];

bool menor(pii f1, pii f2)
{
	return __int128(f1.ff)*__int128(f2.ss) < __int128(f2.ff)*__int128(f1.ss);
}

int main(void)
{
	int n, l;
	scanf("%d %d", &n, &l);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= l; j++)
		{
			scanf("%d", &a[i][j]);

			soma[i] += 1ll*a[i][j];
		}
	}

	for (int i = 1; i <= n; i++)
	{
		int at = 1;
		ll s = 0;

		for (int j = 1; j < n; j++)
		{
			s += soma[i];

			while (at <= l && 1ll*a[i][at]*n <= s)
				s -= 1ll*a[i][at++]*n;

			ll g = __gcd(s + 1ll*(at-1)*a[i][at]*n, 1ll*a[i][at]*n);
			split[i][j] = {(s + 1ll*(at-1)*a[i][at]*n)/g, (1ll*a[i][at]*n)/g};
		}
	}

	vector<int> p;

	for (int i = 1; i < n; i++)
	{
		int ind = 0;

		for (int j = 1; j <= n; j++)
		{
			if (mark[j]) continue;

			if (!ind || menor(split[j][i], split[ind][i]))
				ind = j;
		}

		mark[ind] = 1;

		printf("%lld %lld\n", split[ind][i].ff, split[ind][i].ss);
		p.push_back(ind);
	}

	for (int i = 1; i <= n; i++)
		if (!mark[i])
			p.push_back(i);

	for (auto x: p)
		printf("%d ", x);
	printf("\n");
}
