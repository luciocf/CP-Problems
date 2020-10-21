// CSES 1643 - Maximum Subarray Sum
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	ll ans = -inf;
	ll mn = 0, soma = 0;

	for (int i = 1; i <= n; i++)
	{
		mn = min(mn, soma);
		soma += 1ll*a[i];

		ans = max(ans, soma - mn);
	}

	printf("%lld\n", ans);
}
