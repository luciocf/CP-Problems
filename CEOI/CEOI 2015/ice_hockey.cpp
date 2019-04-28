// CEOI 2015 - Ice Hockey World Championship
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 40;

typedef long long ll;

ll a[maxn];

int main(void)
{
	int n;
	ll m;

	scanf("%d %lld", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);

	int mid = n/2;
	ll ans = 0;

	vector<ll> V;

	for (int mask = 1; mask < (1<<mid); mask++)
	{
		ll sum = 0;
		for (int i = 0; i < mid; i++)
			if (mask&(1<<i))
				sum += a[i];

		if (sum <= m)
		{
			ans++;
			
			V.push_back(sum);
		}
	}

	sort(V.begin(), V.end());

	int k = n-mid;

	for (int mask = 1; mask < (1<<k); mask++)
	{
		ll sum = 0;
		for (int i = mid; i < n; i++)
			if (mask&(1<<(i-mid)))
				sum += a[i];

		if (sum <= m)
		{
			vector<ll>::iterator it = upper_bound(V.begin(), V.end(), m-sum);

			ans += 1ll*(it-V.begin())+1;
		}	
	}

	printf("%lld\n", ans+1);
}
