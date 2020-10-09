// Codeforces 1197E - Culture Code
// Lúcio Cardoso

// Solution is the same as the one in editorial, but without segment tree

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 4e5+10;
const int mod = 1e9+7;

int n;
pii range[maxn];

map<int, int> mp;

int comeca[maxn];
vector<int> termina[maxn];

pii dp[maxn];

int soma[maxn];

void compress(void)
{
	for (int i = 1; i <= n; i++)
		mp[range[i].ff] = mp[range[i].ss] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &range[i].ss, &range[i].ff);

	compress();

	for (int i = 1; i <= n; i++)
	{
		comeca[mp[range[i].ff]]++;
		termina[mp[range[i].ss]].push_back(i);
	}

	for (int i = 2*n; i >= 1; i--)
		soma[i] = soma[i+1] + comeca[i];

	dp[0].ss = 1;

	for (int i = 1; i <= 2*n; i++)
	{
		dp[i] = dp[i-1];

		for (auto ind: termina[i])
		{
			int l = range[ind].ff, r = range[ind].ss;

			if (dp[mp[l]].ff - r + l < dp[i].ff)
			{
				dp[i].ff = dp[mp[l]].ff - r + l;
				dp[i].ss = dp[mp[l]].ss;
			}
			else if (dp[mp[l]].ff - r + l == dp[i].ff) dp[i].ss = (dp[i].ss + dp[mp[l]].ss)%mod;
		}
	}

	int mn = 1e9+10, ans = 0;

	for (int i = 1; i <= n; i++)
	{
		if (soma[mp[range[i].ss]]) continue;

		if (range[i].ff + dp[mp[range[i].ff]].ff < mn)
		{
			mn = range[i].ff + dp[mp[range[i].ff]].ff;
			ans = dp[mp[range[i].ff]].ss;
		}
		else if (range[i].ff + dp[mp[range[i].ff]].ff == mn) ans = (ans + dp[mp[range[i].ff]].ss)%mod;
	}

	printf("%d\n", ans);
}
