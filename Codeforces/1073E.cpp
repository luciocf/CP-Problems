// Codeforces 1073E - Segment Sum
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 20;
const int mod = 998244353;

ll l, r;
int k, pot[maxn];

pii dp[maxn][1<<10][2];

vector<int> dig;

void calc_pot(void)
{
	pot[0] = 1;

	for (int i = 1; i < 20; i++)
		pot[i] = (10ll*pot[i-1])%mod;
}

void add(ll &a, ll b)
{
	a = (a+b)%mod;
}

int solve(void)
{
	int sz = dig.size();
	ll ans = 0;

	for (int sz_at = 1; sz_at <= sz; sz_at++)
	{
		memset(dp, 0, sizeof dp);

		dp[0][0][0].ss = 1;

		for (int pos = 0; pos < sz_at; pos++)
		{
			for (int mask = 0; mask < (1<<10); mask++)
			{
				for (int flag = 0; flag <= 1; flag++)
				{
					for (int i = 0; i < 10; i++)
					{
						if (pos == sz_at-1 && i == 0) continue;

						int mask2 = mask|(1<<i);
						if (__builtin_popcount(mask2) > k) continue;

						ll a = dp[pos][mask][flag].ff, b = dp[pos][mask][flag].ss%mod;
						int aux = (1ll*i*pot[pos])%mod;

						if (sz_at < sz)
						{
							add(dp[pos+1][mask2][flag].ff, ((1ll*aux*b)%mod + a)%mod);
							dp[pos+1][mask2][flag].ss += b;
						}
						else
						{
							int flag2 = 1;
							if (dig[pos] > i || (flag == 0 && dig[pos] == i)) flag2 = 0;

							add(dp[pos+1][mask2][flag2].ff, ((1ll*aux*b)%mod + a)%mod);
							dp[pos+1][mask2][flag2].ss += b;
						}
					}
				}
			}
		}

		for (int mask = 0; mask < (1<<10); mask++)
			add(ans, dp[sz_at][mask][0].ff);
	}

	return ans;
}

int main(void)
{
	calc_pot();

	scanf("%lld %lld %d", &l, &r, &k);

	while (r > 0)
	{
		dig.push_back(r%10);
		r /= 10;
	}

	int ans2 = solve();

	dig.clear();
	l--;
	while (l > 0)
	{
		dig.push_back(l%10);
		l /= 10;
	}

	int ans1 = solve();

	printf("%d\n", (1ll*ans2-1ll*ans1+1ll*mod)%mod);
}
