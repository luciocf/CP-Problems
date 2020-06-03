// Codeforces 1316E - Team Building
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;
const ll inf = 1e18;

int n, p, k;

pii a[maxn];
int s[maxn][8];

ll dp[maxn][1<<7];

bool comp(pii a, pii b) {return a.ff > b.ff;}

ll solve(int pos, int mask)
{
	if (pos == n+1 && mask == (1<<p)-1) return 0;
	if (pos == n+1) return -inf;
	if (dp[pos][mask] != -1) return dp[pos][mask];

	int l = __builtin_popcount(mask);

	ll ans = solve(pos+1, mask);

	if (pos-1-l < k) ans = solve(pos+1, mask) + 1ll*a[pos].ff;

	for (int i = 0; i < p; i++)
	{
		if (mask&(1<<i)) continue;

		int j = a[pos].ss, v = s[j][i];

		ans = max(ans, 1ll*v + solve(pos+1, mask|(1<<i)));
	}

	return dp[pos][mask] = ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &p, &k);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].ff);
		a[i].ss = i;
	}

	sort(a+1, a+n+1, comp);

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < p; j++)
			scanf("%d", &s[i][j]);

	memset(dp, -1, sizeof dp);
	solve(1, 0);

	printf("%lld\n", solve(1, 0));
}
