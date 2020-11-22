// Codeforces 623B - Array GCD
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;
const ll inf = 1e18+10;

int n, x, y, P;
int a[maxn];

vector<int> primes;

ll dp[maxn][3];

void get(int x)
{
	for (int i = 2; i*i <= x; i++)
	{
		if (x%i == 0)
		{
			primes.push_back(i);

			while (x%i == 0)
				x /= i;
		}
	}

	if (x > 1) primes.push_back(x);
}

ll solve(int i, int q)
{
	if (i == n+1) return 0;
	if (dp[i][q] != -1) return dp[i][q];

	ll ans = inf;

	if (q == 0)
	{
		if (a[i]%P == 0)
			ans = min({ans, solve(i+1, 0), solve(i+1, 1)});
		else if (a[i]%P == 1 || a[i]%P == P-1)
			ans = min({ans, 1ll*y + solve(i+1, 0), 1ll*y+solve(i+1, 1)});
	}
	else if (q == 1)
	{
		ans = min({ans, 1ll*x + solve(i+1, 1), 1ll*x + solve(i+1, 2)});
	}
	else
	{
		if (a[i]%P == 0)
			ans = min(ans, solve(i+1, 2));
		else if (a[i]%P == 1 || a[i]%P == P-1)
			ans = min(ans, 1ll*y + solve(i+1, 2));
	}

	return dp[i][q] = ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &x, &y);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	get(a[1]); get(a[1]-1); get(a[1]+1);
	get(a[n]); get(a[n]-1); get(a[n]+1);

	sort(primes.begin(), primes.end());
	primes.erase(unique(primes.begin(), primes.end()), primes.end());

	ll ans = inf;

	for (auto p: primes)
	{
		P = p;
		memset(dp, -1, sizeof dp);

		ans = min(ans, solve(1, 0));

		for (int i = 1; i < n; i++)
			ans = min(ans, 1ll*i*x + solve(i+1, 2));
	}

	printf("%lld\n", ans);
}
