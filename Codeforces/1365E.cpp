// Codeforces 1365E - Maximum Subsequence Value
// Lúcio Cardoso

// Solution is the same as editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;

typedef long long ll;

ll a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);

	ll ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				ans = max(ans, a[i]|a[j]|a[k]);

	printf("%lld\n", ans);
}
