// Codeforces 1358D - The Best Vacation
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e5+10;

typedef long long ll;

int n;
ll x;

int d[maxn];
ll soma[maxn];
ll soma2[maxn];

ll tot(int l, int r)
{
	ll a = 1ll*r*(r+1);
	a /= 2ll;

	ll b = 1ll*l*(l-1);
	b /= 2ll;

	return a-b;
}

ll total(int l, int r, int pos)
{
	if (l == r) return tot(pos, pos+x-1);

	ll a = tot(pos, d[l]);
	ll b = soma2[r-1]-soma2[l];
	ll c = tot(1, x - (1ll*d[l]-1ll*pos+1ll) - soma[r-1]+soma[l]);

	return (a+b+c);
}

int main(void)
{
	scanf("%d %lld", &n, &x);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
		d[i+n] = d[i];
	}

	for (int i = 1; i <= 2*n; i++)
	{
		soma[i] = soma[i-1] + 1ll*d[i];
		soma2[i] = soma2[i-1] + tot(1, d[i]);
	}

	int r = 1;

	ll ans = 1;

	for (int l = 1; l <= n; l++)
	{
		while (r < l || soma[r]-soma[l-1] < x)
			r++;

		if (r > 2*n)
			r = 2*n;

		while (r <= 2*n)
		{
			if (l != r && x - 1 - (soma[r-1]-soma[l]) <= 0)
			{
				r--;
				break;
			}

			int ini = 1, fim = d[l], pos = -1;

			while (ini <= fim)
			{
				int mid = (ini+fim)>>1;

				if (l == r)
				{
					pos = d[l]-x+1;
					break;
				}

				if (x - 1ll*((d[l]-mid+1) + soma[r-1] - soma[l]) > 0)
					pos = mid, fim = mid-1;
				else
					ini = mid+1;
			}

			if (l == r)
			{
				ans = max(ans, total(l, r, pos));
				++r;
				continue;
			}

			int last = x - (1ll*d[l]-1ll*pos+1ll) - soma[r-1]+soma[l];

			if (pos <= last)
				pos += min(d[l]-pos, d[r]-last);

			ans = max(ans, total(l, r, pos));
			++r;
		}
	}

	printf("%lld\n", ans);
}
