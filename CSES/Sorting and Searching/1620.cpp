// CSES 1620 - Factory Machines
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int n, t;
int a[maxn];

bool ok(ll x)
{
	ll tot = 0;

	for (int i = 1; i <= n; i++)
	{
		tot += 1ll*(x/a[i]);

		if (tot >= 1ll*t) return 1;
	}

	return 0;
}

int main(void)
{
	scanf("%d %d", &n, &t);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	ll ini = 0, fim = 1e18+10, ans = 1e18+10;

	while (ini <= fim)
	{
		ll mid = (ini+fim)/2ll;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	printf("%lld\n", ans);
}
