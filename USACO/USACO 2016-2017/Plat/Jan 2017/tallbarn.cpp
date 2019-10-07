// USACO 2016/2017 Plat - Building a Tall Barn
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n;
ll k;

ll a[maxn];

ll tot(double x)
{
	ll qtd = 0;

	for (int i = 1; i <= n; i++)
		qtd += ll((sqrt(1 + 4*a[i]/x) - 1) / 2);

	return qtd;
}

double busca(void)
{
	double ini = 0, fim = 1e18, ans = 0;

	for (int i = 0; i < 300; i++)
	{
		double mid = (ini+fim)/2;

		if (tot(mid) >= k) ans = mid, ini = mid;
		else fim = mid;
	}

	return ans;
}

int main(void)
{
	freopen("tallbarn.in", "r", stdin);
	freopen("tallbarn.out", "w", stdout);

	scanf("%d %lld", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);

	k -= 1ll*n;

	double x = busca();

	ll qtd = 0;
	double ans = 0.0;

	for (int i = 1; i <= n; i++)
	{
		ll y = 1ll*((sqrt(4*a[i]/x + 1) - 1) / 2);

		ans += 1.0*a[i]/(y+1);
		qtd += y;
	}

	ans -= ((k-qtd)*x);

	printf("%lld\n", (ll)round(ans));
}
