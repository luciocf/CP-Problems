// Codeforces 1256E - Yet Another Division Into Teams
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;
const ll inf = 1e18+10;

pii a[maxn];

ll dp[maxn];

int opt[maxn], ans[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].ff);
		a[i].ss = i;
	}

	sort(a+1, a+n+1);

	dp[1] = dp[2] = inf;
	dp[3] = 1ll*(a[3].ff-a[1].ff), opt[3] = 1;

	multiset<pair<ll, int>> st;
	st.insert({-1ll*a[1].ff, 1});

	for (int i = 4; i <= n; i++)
	{
		st.insert({dp[i-3] - 1ll*a[i-2].ff, i-2});

		dp[i] = (*st.begin()).ff + 1ll*a[i].ff;
		opt[i] = (*st.begin()).ss;
	}

	int t = 0;
	for (int i = n; i >= 1; )
	{
		++t;

		int j;
		for (j = i; j >= opt[i]; j--)
			ans[a[j].second] = t;

		i = j;
	}

	printf("%lld %d\n", dp[n], t);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
