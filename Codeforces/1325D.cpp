// Codeforces 1325D - Ehab the Xorcist
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(void)
{
	ll u, v;
	scanf("%lld %lld", &u, &v);

	if (u > v || u%2 != v%2)
	{
		printf("-1\n");
		return 0;
	}

	if (v == 0)
	{
		printf("0\n");
		return 0;
	}

	if (u == v)
	{
		printf("1\n%lld\n", u);
		return 0;
	}

	ll mid = (v-u)/2ll;

	if ((u&mid) == 0) printf("2\n%lld %lld\n", u^mid, mid);
	else printf("3\n%lld %lld %lld\n", u, mid, mid);
}
