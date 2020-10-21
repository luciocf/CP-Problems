// CSES 1074 - Stick Lengths
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	int med = a[n/2];
	ll ans = 0;

	for (int i = 1; i <= n; i++)
		ans += 1ll*abs(a[i]-med);

	printf("%lld\n", ans);
}
