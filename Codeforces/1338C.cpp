// Codeforces 1338C - Perfect Triples
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll pot[30];

int main(void)
{
	int t;
	scanf("%d", &t);

	pot[0] = 1;
	for (int i = 1; i <= 27; i++)
		pot[i] = pot[i-1]*4LL;

	while (t--)
	{
		ll n;
		scanf("%lld", &n);

		int p;
		ll a, b;

		for (int i = 0; i <= 27; i++)
		{
			if (pot[i]-1 >= n)
			{
				p = i-1;
				a = pot[i-1], b = 2LL*pot[i-1];

				break;
			}
		}

		ll grupo = (n-a);

		a += grupo/3LL;
		p *= 2;

		for (int i = 0; i < p; i += 2)
		{
			ll b0, b1;

			b0 = (a&(1LL<<i));
			b1 = (a&(1LL<<(i+1)));

			if (b0 && !b1) b += (1LL<<(i+1));
			else if (!b0 && b1) b += (1LL<<i), b += (1LL<<(i+1));
			else if (b0 && b1) b += (1LL<<i);
		}

		if (grupo%3 == 0) printf("%lld\n", a);
		else if (grupo%3 == 1) printf("%lld\n", b);
		else printf("%lld\n", a^b);
	}
}
