// CSES 1631 - Reading Books
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
 
int n;
int a[maxn];
 
int main(void)
{
	scanf("%d", &n);
 
	ll ans = 0;
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
 
		ans += 1ll*a[i];
	}
 
	int mx = *max_element(a+1, a+n+1);
 
	if (mx > ans-mx) printf("%lld\n", 2*mx);
	else printf("%lld\n", ans);
}
