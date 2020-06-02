// Codeforces 1334E - Divisor Paths
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;

ll fat[100000];

vector<ll> prime;

ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

ll pot(ll a, ll b)
{
	if (!b) return 1;

	ll t = pot(a, b/2);

	if (b%2) return (a*((t*t)%mod))%mod;
	return (t*t)%mod;
}

ll qtd_path(ll x)
{
	ll a = 0, b = 1;

	map<ll, int> mp;

	for (auto p: prime)
	{
		if (x%p == 0)
		{
			x /= p;
			mp[p]++;
		}
	}

	for (auto pp: mp)
	{
		a += pp.second;

		if (pp.second > 1) b = (b*fat[pp.second])%mod;
	}

	a = fat[a];

	return (a*pot(b, mod-2))%mod;
}

int main(void)
{
	ll D;
	scanf("%lld", &D);

	fat[0] = 1;
	for (int i = 1; i < 100000; i++)
		fat[i] = (1ll*i*fat[i-1])%mod;

	for (int i = 2; 1ll*i*i <= D; i++)
	{
		while (D%i == 0)
		{
			prime.push_back(i);
			D /= i;
		}
	}

	if (D > 1) prime.push_back(D);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		ll u, v;
		scanf("%lld %lld", &u, &v);
		if (u > v) swap(u, v);

		ll g = gcd(u, v);

		ll ans = qtd_path(u/g);

		u = g;
		g = gcd(u, v);

		ans = (ans*qtd_path(v/g))%mod;

		printf("%lld\n", ans);
	}
}
