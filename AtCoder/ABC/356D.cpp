// ABC 356D - Masked Popcount
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

const int maxn = 63;
const int mod = 998244353;

ll n, m;
int pos;
int dp[maxn][2];

int solve(int b, int q)
{
    if (b < 0) return 1;
    if (dp[b][q] != -1) return dp[b][q];

    int ans = 0;

    if (b == pos)
    {
        if (q == 1) return dp[b][q] = solve(b-1, 1);
        if (n&(1ll<<b)) return dp[b][q] = solve(b-1, 0);
        return dp[b][q] = 0;
    }

    if (q == 1) return dp[b][q] = (2ll*solve(b-1, 1))%mod;
    
    if (n&(1ll<<b)) return dp[b][q] = (solve(b-1, 0) + solve(b-1, 1))%mod;
    return dp[b][q] = solve(b-1, 0);
}

void solve()
{
    cin >> n >> m;
    
    int ans = 0;
    for (int i = 60; i >= 0; i--)
    {
        if (!(m&(1ll<<i))) continue;
        
        pos = i;
        memset(dp, -1, sizeof dp);
        ans = (ans + solve(60, 0))%mod;
    }

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	while (tc--)
	{
		solve();
	}
}

