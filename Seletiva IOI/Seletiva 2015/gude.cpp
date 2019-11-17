// Seletiva IOI 2015 - Gude
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;

int a[maxn];

int main(void)
{
	int n, S;
	scanf("%d %d", &n, &S);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	long long ans = S;

	for (int i = 2; i <= n; i++)
		ans = min(ans+1ll*S, ans-1ll*a[i-1]+1ll*a[i]);

	printf("%lld\n", ans);
}
