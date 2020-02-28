// COCI 2019/2020 - Trol
// Lúcio Cardoso

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main(void)
{
	int q;
	scanf("%d", &q);

	while(q--)
	{
		long long l, r;

		scanf("%lld %lld", &l, &r);

		if (r-l+1 <= 9)
		{
			int ans = 0;
			for (ll i = l; i <= r; i++)
			{
				ll x = i%9;
				if (x == 0) x = 9;

				ans += x;
			}

			printf("%d\n", ans);
		}
		else
		{
			ll ans = 0;

			ll a;
			for (ll i = l; i <= r; i++)
			{
				ll x = i%9;
				if (x == 0) x = 9;

				ans += 1ll*x;
				if (x == 9)
				{
					a = i+1;
					break;
				}
			}

			ll b;
			for (ll i = r; i >= l; i--)
			{
				ll x = i%9;
				if (x == 0) x = 9;

				ans += x;
				if (x == 1)
				{
					b = i-1;
					break;
				}
			}

			ans += 45ll*((b-a+1)/9);

			printf("%lld\n", ans);
		}
	}
}
