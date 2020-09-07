// Codeforces 315E - Sereja and Subsequences
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e6+10;
const int mod = 1e9+7;
 
int tot[maxn];
int last[maxn];
 
struct FenwickTree
{
	int bit[maxn];
 
	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] = (bit[x] + v)%mod;
	}
 
	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans = (ans + bit[x])%mod;
		return ans;
	}
} B;
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
 
		tot[i] = (x + ((1ll*B.soma(x)*x)%mod))%mod;
 
		if (last[x]) B.upd(x, mod-tot[last[x]]);
		B.upd(x, tot[i]);
 
		last[x] = i;
	}
 
	int ans = 0;
 
	for (int i = 1; i < maxn; i++)
		if (last[i])
			ans = (ans + tot[last[i]])%mod;
 
	printf("%d\n", ans);
}
