// Neps Academy - Liga de Programação 2020 - Etapa 1 - Produto Triplo
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	int q_neg = 0, q_pos = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		if (a[i] < 0) q_neg++;
		else q_pos++;
	}

	if (n == 3 || q_pos == 0)
	{
		printf("%lld\n", 1ll*a[n]*a[n-1]*a[n-2]);
		return 0;
	}

	ll caso1 = -inf, caso2 = -inf;

	if (q_pos >= 3) caso1 = 1ll*a[n]*a[n-1]*a[n-2];

	if (q_neg >= 2) caso2 = 1ll*a[1]*a[2]*a[n];

	printf("%lld\n", max(caso1, caso2));
}
