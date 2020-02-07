// Brazilian ICPC Summer School 2020 - Day 9 - The Imp
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;
const ll inf = 1e18;

int n, k;

pii a[maxn];

ll dp[maxn][11];
bool mark[maxn][11];

ll solve(int i, int p)
{
	if (i == n+1) return 0;
	if (mark[i][p]) return dp[i][p];

	mark[i][p] = 1;

	ll caso1 = solve(i+1, p);

	if (p == k+1)
		return dp[i][p] = max(1ll*a[i].first-1ll*a[i].second, caso1);

	ll caso2 = 1ll*a[i].first-1ll*a[i].second;
	ll caso3 = solve(i+1, p+1)-1ll*a[i].second;

	return dp[i][p] = max(caso1, min(caso2, caso3));
}

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		scanf("%d %d", &n, &k);

		for (int i = 1; i <= n; i++)
			scanf("%d %d", &a[i].first, &a[i].second);

		sort(a+1, a+n+1);

		memset(mark, 0, sizeof mark);

		printf("%lld\n", max(0ll, solve(1, 1)));
	}
}
