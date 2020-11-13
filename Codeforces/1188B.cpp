// Codeforces 1188B - Count Pairs
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(void)
{
	int n, p, k;
	scanf("%d %d %d", &n, &p, &k);

	map<ll, int> mp;

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		int a = (1ll*((1ll*x*x)%p)*((1ll*x*x)%p))%p;
		int b = (1ll*k*x)%p;

		mp[(a - b + p)%p]++;
	}

	ll ans = 0;
	for (auto pp: mp)
		ans += (1ll*pp.second*(pp.second-1)/2ll);

	printf("%lld\n", ans);
}
