// Codeforces 675C - Money Transfers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	map<ll, int> mp;
	ll s = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		s += 1ll*a[i];
		mp[s]++;
	}

	int ans = n;
	s = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = min(ans, n-mp[s]);
		s += a[i];
	}

	printf("%d\n", ans);
}
