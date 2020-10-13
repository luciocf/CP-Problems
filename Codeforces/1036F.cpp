// Codeforces 1036F - Relatively Prime Powers
// Lúcio Cardoso

// Solution is the same as the first one mentioned in the editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll get_sqrt(ll n)
{
	ll ini = 1, fim = 1000000000, ans;

	while (ini <= fim)
	{
		ll mid = (ini+fim)/2ll;

		if (mid*mid > n) fim = mid-1;
		else ans = mid, ini = mid+1;
	}

	return ans;
}

ll pot[1000010];
bool sq[1000010];

int main(void)
{
	vector<ll> V;

	for (int i = 1; i <= 1000000; i++)
	{
		pot[i] = 1ll*i*i;
		if (pot[i] <= 1000000ll) sq[pot[i]] = 1;
	}

	for (int k = 3; k < 70; k++)
	{
		for (int i = 2; i <= 1000000 && 1ll*pot[i]*i <= 1000000000000000000ll; i++)
		{
			pot[i] = 1ll*i*pot[i];

			if (k&1 && !sq[i]) V.push_back(pot[i]);
		}
	}

	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()), V.end());

	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		ll n;
		scanf("%lld", &n);

		ll ans = n - get_sqrt(n);

		ans -= (ll)((upper_bound(V.begin(), V.end(), n)-V.begin()));

		printf("%lld\n", ans);
	}
}
