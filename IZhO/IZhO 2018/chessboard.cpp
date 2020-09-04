#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
typedef long long ll;
 
const int maxn = 1e5+10;
const ll inf = 1e18+10;
 
pair<pii, pii> rect[maxn];
 
ll qtd(int k, int d)
{
	if (k < 0) return 0;
	++k;
	int oldk = k;
 
	ll ans = (k/(2*d))*d;
	k -= ((k/(2*d))*(2*d));
 
	return (ans+min(d, k));
}
 
ll get_menor(int i, int d)
{
	ll linha = qtd(rect[i].ss.ss, d)-qtd(rect[i].ff.ss-1, d);
	ll col = qtd(rect[i].ss.ff, d)-qtd(rect[i].ff.ff-1, d);
 
	return linha*col;
}
 
ll get_maior(int i, int d)
{
	ll linha = (rect[i].ss.ss-rect[i].ff.ss+1) - (qtd(rect[i].ss.ss, d)-qtd(rect[i].ff.ss-1, d));
	ll col = (rect[i].ss.ff-rect[i].ff.ff+1) - (qtd(rect[i].ss.ff, d)-qtd(rect[i].ff.ff-1, d));
 
	return linha*col;
}
 
int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
 
	for (int i = 1; i <= k; i++)
	{
		scanf("%d %d", &rect[i].ff.ff, &rect[i].ff.ss);
		scanf("%d %d", &rect[i].ss.ff, &rect[i].ss.ss);
 
		rect[i].ff.ff--, rect[i].ff.ss--;
		rect[i].ss.ff--, rect[i].ss.ss--;
	}
 
	vector<int> D;
 
	for (int d = 1; d*d <= n; d++)
	{
		if (n%d) continue;
 
		D.push_back(d);
		if (n/d != d) D.push_back(n/d);
	}
 
	ll ans = inf; 
 
	for (auto d: D)
	{
		if (d == n) continue;
 
		ll p = 0, b = 0;
 
		for (int i = 1; i <= k; i++)
		{
			ll x = get_menor(i, d) + get_maior(i, d);
 
			p += x;
 
			b += (1ll*(rect[i].ss.ff-rect[i].ff.ff+1)*(rect[i].ss.ss-rect[i].ff.ss+1) - x);
		}
 
		ll x = ((n+2*d-1)/(2*d));
		ll y = n/(2*d);
 
		ll tot_p = 1ll*d*d*(x*x+y*y);
 
		ans = min(ans, (tot_p-p)+b);
 
		swap(p, b);
		tot_p = 1ll*n*n-tot_p;
 
		ans = min(ans, (tot_p-p)+b);
	}
 
	printf("%lld\n", ans);
}
