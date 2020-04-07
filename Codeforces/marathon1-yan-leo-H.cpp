// Codeforces 1st Marathon - Yan and Leo - H - Max and Min
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int maxn = 2e4+10;
const int maxk = 110;
const int inf = 1e7+10;
 
struct S
{
	int v;
	ll tot;
};
 
int a[maxn];
ll dp[maxn][maxk];
 
stack<S> stk_mx[maxk], stk_mn[maxk];
multiset<ll> st_mx[maxk], st_mn[maxk];
 
int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= min(i, k); j++)
		{
			while (stk_mx[j].size() && a[i] > stk_mx[j].top().v)
			{
				st_mx[j].erase(st_mx[j].find(-stk_mx[j].top().tot));
 
				stk_mx[j].pop();
			}
 
			while (stk_mn[j].size() && a[i] < stk_mn[j].top().v)
			{
				st_mn[j].erase(st_mn[j].find(-stk_mn[j].top().tot));
 
				stk_mn[j].pop();
			}
 
			stk_mx[j].push({a[i], 1ll*a[i] + dp[i-1][j-1]});
			st_mx[j].insert(-1ll*(1ll*a[i] + dp[i-1][j-1]));
 
			stk_mn[j].push({a[i], -1ll*a[i] + dp[i-1][j-1]});
			st_mn[j].insert(-1ll*(-1ll*a[i] + dp[i-1][j-1]));
 
			dp[i][j] = dp[i-1][j];
 
			dp[i][j] = max(dp[i][j], -1ll*a[i] - *st_mx[j].begin());
 
			dp[i][j] = max(dp[i][j], 1ll*a[i] - *st_mn[j].begin());
		}
	}
 
	printf("%lld\n", dp[n][k]);
}
