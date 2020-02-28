// COCI 2019/2020 - Lutrija
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool prime(ll x)
{
	if (x <= 1) return 0;

	for (int i = 2; 1ll*i*i <= x; i++)
		if (x%i == 0)
			return false;

	return true; 
}

int main(void)
{
	ll a, b;
	scanf("%lld %lld", &a, &b);

	if (abs(b-a) == 2)
	{
		printf("2\n%lld %lld\n", a, b);
		return 0;
	}

	if (b-a == 4 && prime(a+2))
	{
		printf("3\n%lld %lld %lld\n", a, a+2, b);
		return 0;
	}

	if (a-b == 4 && prime(b+2))
	{
		printf("3\n%lld %lld %lld\n", b, b+2, a);
		return 0;
	}

	if (a < b)
	{
		if (a == 2)
		{
			if (prime(b-2)) printf("2\n2 %lld\n", b);
			else if (prime(b+2)) printf("3\n2 %lld %lld\n", b+2, b);
			else printf("-1\n");
		}
		else
		{
			if (!prime(a-2) && !prime(a+2)) printf("-1\n");
			else
			{
				if (!prime(b-2) && !prime(b+2)) printf("-1\n");
				else
				{
					if (prime(a-2) && prime(b-2)) printf("3\n%lld 2 %lld\n", a, b);
					else if (prime(a-2) && prime(b+2)) printf("4\n%lld 2 %lld %lld\n", a, b+2, b);
					else if (prime(a+2) && prime(b-2)) printf("4\n%lld %lld 2 %lld\n", a, a+2, b);
					else printf("5\n%lld %lld 2 %lld %lld\n", a, a+2, b+2, b);
				}
			}
		}
	}
	else
	{
		if (b == 2)
		{
			if (prime(a-2)) printf("2\n%lld 2\n", a);
			else if (prime(a+2)) printf("3\n%lld %lld 2\n", a, a+2);
			else printf("-1\n");
		}
		else
		{
			if (!prime(b-2) && !prime(b+2)) printf("-1\n");
			else
			{
				if (!prime(a-2) && !prime(a+2)) printf("-1\n");
				else
				{
					if (prime(b-2) && prime(a-2)) printf("3\n%lld 2 %lld\n", a, b);
					else if (prime(b-2) && prime(a+2)) printf("4\n%lld 2 %lld %lld\n", a, a+2, b);
					else if (prime(b+2) && prime(a-2)) printf("4\n%lld 2 %lld %lld\n", a, b+2, b);
					else printf("5\n%lld %lld 2 %lld %lld\n", a, a+2, b+2, b);
				}
			}
		}
	}
}
