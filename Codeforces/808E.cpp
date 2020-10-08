// Codeforces 808E - Selling Souvenirs
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 3e5+10;

vector<int> a[4];

pair<ll, pii> dp[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		int w, c;
		scanf("%d %d", &w, &c);

		a[w].push_back(c);
	}

	sort(a[1].begin(), a[1].end(), greater<int>());
	sort(a[2].begin(), a[2].end(), greater<int>());
	sort(a[3].begin(), a[3].end(), greater<int>());

	for (int i = 0; i < m; i++)
	{
		int l = dp[i].ss.ff, r = dp[i].ss.ss;

		dp[i+1] = max(dp[i+1], dp[i]);
		dp[i+2] = max(dp[i+2], dp[i]);

		if (l < a[1].size())
			dp[i+1] = max(dp[i+1], {dp[i].ff + 1ll*a[1][l], {l+1, r}});

		if (l > 0 && r < a[2].size())
			dp[i+1] = max(dp[i+1], {dp[i].ff - 1ll*a[1][l-1] + 1ll*a[2][r], {l-1, r+1}});

		if (r < a[2].size())
			dp[i+2] = max(dp[i+2], {dp[i].ff + 1ll*a[2][r], {l, r+1}}); 
	}

	ll ans = dp[m].ff, pref = 0;

	for (int i = 1; 3*i <= m && i-1 < a[3].size(); i++)
	{
		pref += 1ll*a[3][i-1];
		ans = max(ans, pref + dp[m-3*i].ff);
	}

	printf("%lld\n", ans);
}
