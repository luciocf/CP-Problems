// Codeforces 367C - Sereja and the Arrangement of Numbers
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e6+10;

int a[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d %d", &x, &a[i]);
	}

	sort(a+1, a+m+1, greater<int>());

	if (n == 1)
	{
		printf("%d\n", a[1]);
		return 0;
	}

	ll ans = a[1]+a[2], aux = ans;

	for (int i = 3; i <= m; i++)
	{
		aux += 1ll*a[i];

		ll x = (1ll*i*(i-1)/2ll + 1ll) + ((i%2) ? 0 : i/2-1);

		if (x <= 1ll*n) ans = aux;
	}

	printf("%lld\n", ans);
}
