// Codeforces 551C - GukiZ hates Boxes
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n, m;
int a[maxn], b[maxn];

bool ok(ll t)
{
	for (int i = 1; i <= n; i++)
		b[i] = a[i];

	int ptr = n;

	for (int i = 1; i <= m; i++)
	{
		ll x = t;

		if (ptr == 0) break;

		while (ptr > 0 && b[ptr] == 0)
			ptr--;

		x -= (ptr-1);

		while (x > 0 && ptr > 0)
		{
			if (b[ptr] == 0)
			{
				ptr--;
				continue;
			}

			if (b[ptr] >= x)
			{
				b[ptr] -= x;
				break;
			}

			x -= b[ptr], b[ptr] = 0;
			ptr--;
		}
	}

	for (int i = 1; i <= n; i++)
		if (b[i])
			return false;

	return true;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	ll ini = 0, fim = 1e18, ans = 1e18;

	while (ini <= fim)
	{
		ll mid = (ini+fim)/2ll;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	printf("%lld\n", ans+1);
}
