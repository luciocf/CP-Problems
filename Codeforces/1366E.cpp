// Codeforces 1366E - Two Arrays
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;
const int mod = 998244353;

int a[maxn], b[maxn];
int mn[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	mn[n] = a[n];
	for (int i = n-1; i >= 1; i--)
		mn[i] = min(mn[i+1], a[i]);

	if (mn[1] != b[1])
	{
		printf("0\n");
		return 0;
	}

	int ans = 1;
	for (int i = 2; i <= m; i++)
	{
		int qtd = (int)(upper_bound(mn+1, mn+n+1, b[i]) - lower_bound(mn+1, mn+n+1, b[i]));

		ans = (1ll*ans*qtd)%mod;
	}

	printf("%d\n", ans);
}
