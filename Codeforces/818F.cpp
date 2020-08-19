// Codeforces 818F - Level Generation
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool ok(int x, int n)
{
	return (2ll*(n-x-1) >= 1ll*(n-1) + 1ll*x*(x-1)/2ll);
}

int main(void)
{
	int q;
	scanf("%d", &q);

	while (q--)
	{
		int n;
		scanf("%d", &n);

		int ini = 1, fim = n-1, x = 1;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (ok(mid, n)) x = mid, ini = mid+1;
			else fim = mid-1;
		}

		ll ans = 1ll*(n-1) + 1ll*x*(x-1)/2ll;

		ll k = max(0ll, 1ll*n - 2ll*x - 1ll*x*(x-1)/2ll - 3);

		printf("%lld\n", ans+k);
	}
}
