// IOI 2005 - Mean Sequence
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e6+10;
const long long inf = 2e18+10;

typedef long long ll;

ll minP, minI;

int main(void)
{
	int n;
	scanf("%d", &n);

	ll P = 0, I = 0;
	minP = minI = inf;

	for (int i = 1; i <= n; i++)
	{
		ll M;
		scanf("%lld", &M);
		M *= 2ll;

		if (i&1)
		{
			ll num = M + 2*(I-P);
			minI = min(minI, num);

			I += M;
		}
		else
		{
			ll num = M + 2*(P-I);
			minP = min(minP, num);

			P += M;
		}
	}

	ll ini = -minP/2;
	if (minP+ini < 0) minP++;

	ll fim = minI/2;
	if (minI-2*fim < 0) minI--;

	printf("%lld\n", max(0ll, fim-ini+1));
}
