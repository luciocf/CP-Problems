// Codeforces 1328F - Make k Equal
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int n, k;
int a[maxn];

ll pref[maxn], suf[maxn];

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	for (int i = 1; i <= n; i++)
		pref[i] = pref[i-1] + 1ll*a[i];

	for (int i = n; i >= 1; i--)
		suf[i] = suf[i+1] + 1ll*a[i];

	ll ans = 2e18;

	for (int l = 1; l <= n; l++)
	{
		int r = l;
		while (r < n && a[r+1] == a[l])
			r++;

		ll cost_pref = 1ll*(a[l]-1)*(l-1) - pref[l-1];
		ll cost_suf = suf[r+1] - 1ll*(a[l]+1)*(n-r);

		ll aux = 0;
		int x = k-(r-l+1);

		if (x <= 0)
		{
			printf("0\n");
			return 0;
		}

		if (l > 1 && l-1 >= x)
		{
			aux += cost_pref;
			aux += 1ll*min(x, l-1);

			ans = min(ans, aux);
		}

		aux = 0;

		if (r < n && n-r >= x)
		{
			aux += cost_suf;
			aux += 1ll*min(x, n-r);

			ans = min(ans, aux);
		}

		aux = cost_pref + cost_suf + 1ll*x;

		ans = min(ans, aux);
		l = r;
	}

	printf("%lld\n", ans);
}
