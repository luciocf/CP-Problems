// IZhO 2017 - Bootfall
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 510;
const int maxs = 250010;
const int mod = 1e9+7;
 
int a[maxn];
int dp[maxs], qtd[maxs];
 
int main(void)
{
	int n;
	scanf("%d", &n);
 
	int s = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		s += a[i];
	}
 
	dp[0] = 1;
 
	for (int i = 1; i <= n; i++)
		for (int j = maxs-1; j >= a[i]; j--)
			dp[j] = (dp[j] + dp[j - a[i]])%mod;
 
	if (s&1 || !dp[s/2])
	{
		printf("0\n");
		return 0;
	}
 
	for (int i = 1; i <= n; i++)
	{
		for (int j = a[i]; j < maxs; j++)
			dp[j] = (dp[j] - dp[j - a[i]] + mod)%mod;
 
		for (int j = (s-a[i]+1)/2; j < maxs; j++)
			if (dp[j])
				qtd[2*j-s+a[i]]++;
 
		for (int j = maxs; j >= a[i]; j--)
			dp[j] = (dp[j] + dp[j - a[i]])%mod;
	}
 
	int ans = 0;
	for (int i = 1; i < maxs; i++)
		if (qtd[i] == n)
			ans++;
 
	printf("%d\n", ans);
	for (int i = 1; i < maxs; i++)
		if (qtd[i] == n)
			printf("%d ", i);
	printf("\n");
}
