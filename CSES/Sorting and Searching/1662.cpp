// CSES 1662 - Subarray Divisibility
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
 
int a[maxn];
int qtd[maxn];
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
 
	ll ans = 0;
	ll soma = 0;
 
	qtd[0] = 1;
 
	for (int i = 1; i <= n; i++)
	{
		soma = (soma+1ll*a[i])%n;
		soma = (soma+n)%n;
 
		ans += 1ll*qtd[soma];
 
		qtd[soma]++;
	}
 
	printf("%lld\n", ans);
}
