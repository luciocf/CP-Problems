// Codeforces 1151E - Number of Components
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	long long ans = 0;
	for (int i = 2; i <= n; i++)
	{
		int l = min(a[i], a[i-1]);
		int r = max(a[i], a[i-1]);

		if (l != r)
			ans += 1ll*(r-l)*(n+l-r+1);
	}

	ans += 1ll*a[1]*(n-a[1]+1);
	ans += 1ll*a[n]*(n-a[n]+1);

	printf("%lld\n", ans/2ll);
}
