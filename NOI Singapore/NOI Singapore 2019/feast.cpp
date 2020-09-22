// NOI Singapore 2019 - Feast
// Lúcio Cardoso

// Solution: We can use Alien's Trick to solve the problem.

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
const int maxn = 3e5+10;
const ll inf = 6e14+10;
 
int n;
int a[maxn];
 
ll pref[maxn];
 
ll dp[maxn];
pii range[maxn];
 
void get(ll c)
{	
	ll mx = 0;
	int mx_l = 0, mx_r = 0;
 
	for (int i = 1; i <= n; i++)
	{ 	
		ll v = pref[i] + mx - c;

 		dp[i] = dp[i-1], range[i] = range[i-1];

 		if (v > dp[i])
 		{
 			dp[i] = v;
 			range[i] = {mx_l+1, mx_r+1};
 		}
 		else if (v == dp[i])
 		{
 			range[i].ff = min(range[i].ff, mx_l+1);
 			range[i].ss = max(range[i].ss, mx_r+1);
 		}

 		v = dp[i] - pref[i];

 		if (v > mx)
 		{
 			mx = v;
 			mx_l = range[i].ff, mx_r = range[i].ss;
 		}
 		else
 		{
 			mx_l = min(mx_l, range[i].ff);
 			mx_r = max(mx_r, range[i].ss);
 		}
	}
}
 
int main(void)
{
	int k;
	scanf("%d %d", &n, &k);
 
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
 
		pref[i] = pref[i-1]+1ll*a[i];
	}
 
	ll ini = 0, fim = inf, best = inf;
 
	while (ini <= fim)
	{
		ll mid = (ini+fim)/2ll;

		get(mid);
 
		if (range[n].ff > k) ini = mid+1;
		else best = mid, fim = mid-1;
	}
 
	get(best);

	int qtd = min(k, range[n].ss);

	printf("%lld\n", dp[n] + 1ll*qtd*best);
}
