// CSES 1085 - Array Division
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e5+10;
 
int n, k;
int a[maxn];
 
bool ok(ll x)
{
	int qtd = 1;
	ll tot = 0;
 
	for (int i = 1; i <= n; i++)
	{
		if (tot+1ll*a[i] > x)
		{
			tot = a[i];
			qtd++;
		}
		else tot += 1ll*a[i];
	}
 
	return (qtd <= k);
}
 
ll busca(int mx)
{
	ll ini = mx, fim = 1e15+10, ans = 1e15+10;
 
	while (ini <= fim)
	{
		ll mid = (ini+fim)>>1;
 
		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1;
	}
 
	return ans;
}
 
int main(void)
{
	scanf("%d %d", &n, &k);
 
	int mx = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mx = max(mx, a[i]);
	}
 
	printf("%lld\n", busca(mx));
}
