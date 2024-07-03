// Codeforces 1353E - K-periodic Garland
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e6+10;

int n, k;
string s;

int pref[2][maxn];
int dp[maxn];

int solve(int i)
{
    if (dp[i] != -1) return dp[i];
    
    int x = (s[i-1] == '0' ? 1 : 0);
    int ans = x + pref[1][n]-pref[1][i];
    if (i+k <= n) ans = min(ans, x + solve(i+k) + pref[1][i+k-1]-pref[1][i]);

    return dp[i] = ans;
}

void solve()
{
    cin >> n >> k >> s;

    for (int i = 1; i <= n; i++)
    {
        pref[0][i] = pref[1][i] = 0;
        dp[i] = -1;
    }

    for (int i = 1; i <= n; i++)
    {
        pref[0][i] = pref[0][i-1] + (s[i-1] == '0' ? 1 : 0);
        pref[1][i] = pref[1][i-1] + (s[i-1] == '1' ? 1 : 0);
    }

    int ans = pref[1][n];
    for (int i = 1; i <= n; i++)
        ans = min(ans, pref[1][i-1] + solve(i));

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
 
