// TIMUS 1217 - Unlucky Tickets
// Lúcio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 22;
const int maxs = 100;

int n;
ll dp[maxn][2*maxs][2*maxs];

ll solve(int i, int s1, int s2)
{
	if (i == n+1)
	{
		if (s1 == 90 and s2 == 90) return 1;
		return 0;
	}

	if (dp[i][s1][s2] != -1) return dp[i][s1][s2];

	ll ans = 0;
	for (int d = 0; d < 10; d++)
	{
		int t1 = s1, t2 = s2;

		if (i <= n/2) t1 += d;
		else t1 -= d;

		if (i%2) t2 += d;
		else t2 -= d;

		ans += solve(i+1, t1, t2);
	}

	return dp[i][s1][s2] = ans;
}

int main(void)
{
	cin >> n;

	memset(dp, -1, sizeof dp);
	cout << solve(1, 90, 90) << "\n";
}
