// COCI 2017/2018 - Cover
// Lúcio Cardoso

// Solution: https://codeforces.com/blog/entry/57508?#comment-411980

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 5e3+10;
const long long inf = 2e18+10;

typedef pair<int, int> pii;
typedef long long ll;

int n;
int prox[maxn];

ll dp[maxn];

pii pt[maxn];

bool comp(pii a, pii b)
{
	if (a.ff != b.ff) return a.ff < b.ff;
	return a.ss < b.ss;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &pt[i].ff, &pt[i].ss);

		pt[i].ff = abs(pt[i].ff);
		pt[i].ss = abs(pt[i].ss);
	}

	sort(pt+1, pt+n+1, comp);

	for (int i = 1; i <= n; i++)
	{
		for (int j = i-1; j >= 1; j--)
		{
			if (pt[j].ss > pt[i].ss)
			{
				prox[i] = j;
				break;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		dp[i] = inf;

	for (int i = 1; i <= n; i++)
	{
		int at = i;

		while (at != 0)
		{
			dp[i] = min(dp[i], 4ll*pt[i].ff*pt[at].ss + dp[prox[at]]);
			at = prox[at];
		}
	}

	printf("%lld\n", dp[n]);
}
