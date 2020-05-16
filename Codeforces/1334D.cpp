// Codeforces 1334D - Minimum Euler Cycle
// Lúcio Cardoso

// Solution: Same as editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n;
		ll l, r;
		scanf("%d %lld %lld", &n, &l, &r);

		ll soma = 0;
		int x = 0;
		for (int i = 1; i < n; i++)
		{
			if (soma + 2ll*(n-i) >= l) break;
			soma += 2ll*(n-i), x++;
		}

		x++, soma++;
		int y = x+1;

		while (soma <= r)
		{
			if (x == n)
			{
				printf("1");
				break;
			}

			if (soma >= l && soma <= r) printf("%d ", x);

			soma++;

			if (soma >= l && soma <= r) printf("%d ", y);

			soma++;

			if (y+1 == n+1)
			{
				x++;
				y = x+1;
			}
			else y++;
		}

		printf("\n");
	}
}
