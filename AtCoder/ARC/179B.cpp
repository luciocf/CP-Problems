// ARC 179B - Between B and B
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e4+10;
const int maxm = 10;
const int mod = 998244353;

int n, m;
int a[maxn];
int dp[maxn][1<<maxm], t[maxm];

int solve(int i, int mask)
{
	if (i == n+1) return 1;
	if (dp[i][mask] != -1) return dp[i][mask];

	int ans = 0;
	for (int j = 0; j < m; j++)
	{
		if (mask&(1<<j))
		{
			int newMask = mask | t[j];
			if (a[j] != j) newMask ^= (1<<j);

			ans = (ans + solve(i+1, newMask))%mod;
		}
	}

	return dp[i][mask] = ans;
}

int main(void)
{
	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		cin >> a[i];
		a[i]--;

		t[a[i]] += (1<<i);
	}

	memset(dp, -1, sizeof dp);
	cout << solve(1, (1<<m)-1) << "\n";
}
