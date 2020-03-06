// Codeforces 1305F - Kuroni and the Punishment
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

ll a[maxn];

vector<ll> prime;

void get_fact(ll x)
{
	prime.clear();

	for (int i = 2; 1ll*i*i <= x; i++)
	{
		if (x%i == 0)
		{
			prime.push_back(i);

			while (x%i == 0)
				x /= i;
		}
	}

	if (x > 1) prime.push_back(x);
}

int main(void)
{
	srand(time(0));
    mt19937 rng(rand());

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);

	int ans = n;
	for (int t = 1; t <= 25; t++)
	{
		int pos = rng()%n+1;

		if (a[pos] > 2)
		{
			get_fact(a[pos]-1);

			for (auto p: prime)
			{
				ll aux = 0;
				for (int i = 1; i <= n; i++)
				{
					if (a[i]-(a[i]%p) > 0)
						aux += min(a[i]%p, p-(a[i]%p));
					else
						aux += p-(a[i]%p);
				}

				if (aux <= n) ans = min(1ll*ans, aux);
			}
		}

		if (a[pos] > 1)
		{
			get_fact(a[pos]);

			for (auto p: prime)
			{
				ll aux = 0;
				for (int i = 1; i <= n; i++)
				{
					if (a[i]-(a[i]%p) > 0)
						aux += min(a[i]%p, p-(a[i]%p));
					else
						aux += p-(a[i]%p);
				}

				if (aux <= n) ans = min(1ll*ans, aux);
			}
		}

		get_fact(a[pos]+1);

		for (auto p: prime)
		{
			ll aux = 0;
			for (int i = 1; i <= n; i++)
			{
				if (a[i]-(a[i]%p) > 0)
					aux += min(a[i]%p, p-(a[i]%p));
				else
					aux += p-(a[i]%p);
			}

			if (aux <= n) ans = min(1ll*ans, aux);
		}
	}

	printf("%d\n", ans);
}
