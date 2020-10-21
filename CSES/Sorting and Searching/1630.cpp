// CSES 1630 - Tasks and Deadlines
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int a[maxn], b[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &a[i], &b[i]);

		ans += 1ll*b[i];
	}

	sort(a+1, a+n+1, greater<int>());

	for (int i = 1; i <= n; i++)
		ans -= 1ll*a[i]*i;
	
	printf("%lld\n", ans);
}
