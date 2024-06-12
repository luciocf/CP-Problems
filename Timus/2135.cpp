// Timus 2135 - Pauline and commits
// Lucio Figueiredo

// Very simple DP --- product gets large quickly if we ignore 1s

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

const int maxn = 1e5+10;

int n;
ll l, r;
int a[maxn];
int dp[maxn];

int solve(int i)
{
	if (i == n+1) return 0;
	if (dp[i] != -1) return dp[i];

	int ans = maxn;
	ll prod = a[i];

	if (prod >= l and prod <= r) ans = min(ans, 1+solve(i+1));
	for (int j = i+1; j <= n; j++)
	{
		if (j < n and a[j] == 1) continue;
		if (prod > r/a[j]+1) break;
		prod *= a[j];
		if (prod >= l and prod <= r) ans = min(ans, 1+solve(j+1));
	}

	return dp[i] = ans;
}

int main(void)
{
	cin >> n >> l >> r;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	memset(dp, -1, sizeof dp);
	int ans = solve(1);

	if (ans == maxn) cout << "-1\n";
	else cout << ans << "\n";
}
