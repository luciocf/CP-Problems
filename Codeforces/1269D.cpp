// Codeforces 1269D - Domino for Young
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(void)
{
	int n;
	scanf("%d", &n);

	ll lado1 = 0, lado2 = 0;

	for (int i = 1; i <= n; i++)
	{
		ll a;
		scanf("%lld", &a);

		if (i%2 == 0) lado1 += (a+1)/2, lado2 += a/2;
		else lado1 += a/2, lado2 += (a+1)/2;
	}

	printf("%lld\n", min(lado1, lado2));
}
