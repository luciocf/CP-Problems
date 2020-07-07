// Codeforces 1166D - Cute Sequences
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll pot[51];

void solve(void)
{
	ll a, b, m;
	scanf("%lld %lld %lld", &a, &b, &m);

	if (a == b)
	{
		printf("1 %lld\n", a);
		return;
	}

	ll old_b = b;

	for (ll n = 2; n <= 50 && pot[n-2]*a < old_b; n++)
	{
		b = old_b;

		b -= pot[n-2]*a;
		b -= (pot[n-2]-1ll);

		if (b <= 0) break;

		vector<ll> ans;

		for (int i = n-3; i >= 0; i--)
		{
			ll x = ((b%pot[i] == 0) ? (b/pot[i])-1ll : b/pot[i]);
			x = min(m-1, x);
			x = max(0ll, x);

			b -= pot[i]*x;

			ans.push_back(x+1);
		}

		if (b > m) continue;

		printf("%lld %lld", n, a);

		for (int i = 0; i < (int)ans.size(); i++)
		{
			ll k = ans[i] + pot[i]*a;

			for (int j = 0; j < i; j++)
				k += pot[i-j-1]*ans[j];

			printf(" %lld", k);
		}
		printf(" %lld\n", old_b);
		return;
	}

	printf("-1\n");
}

int main(void)
{
	int tc;
	scanf("%d", &tc);

	pot[0] = 1;
	for (int i = 1; i <= 50; i++)
		pot[i] = 2ll*pot[i-1];

	while (tc--)
	{
		solve();
	}
}
